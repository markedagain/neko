/******************************************************************************
Filename: Program.cs

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Drawing;

namespace NekoPak {
  class Program {

    [DllImport("neko.dll")]
    static extern int pak_create([MarshalAs(UnmanagedType.LPStr)] string filename);

    [DllImport("neko.dll")]
    static extern IntPtr pak_open([MarshalAs(UnmanagedType.LPStr)] string filename);

    [DllImport("neko.dll")]
    static extern int pak_insert(IntPtr pak, [MarshalAs(UnmanagedType.LPStr)] string filename, [MarshalAs(UnmanagedType.LPStr)] string nameInPak);

    [DllImport("neko.dll")]
    static extern int pak_insert_data(IntPtr pak, [MarshalAs(UnmanagedType.LPStr)] string nameInPak, IntPtr data, uint dataSize);

    [DllImport("neko.dll")]
    static extern int pak_close(IntPtr pak);

    public static Point AddTextureToPak(string file, string storeName, IntPtr pak) {
      Bitmap bmp = (Bitmap)Image.FromFile(file);
      ushort width = Convert.ToUInt16(bmp.Width);
      ushort height = Convert.ToUInt16(bmp.Height);
      List<byte> data = new List<byte>();
      foreach (byte b in BitConverter.GetBytes((uint)bmp.Width))
        data.Add(b);
      foreach (byte b in BitConverter.GetBytes((uint)bmp.Height))
        data.Add(b);
      Console.WriteLine(width.ToString() + "x" + height.ToString());
      for (int i = 0; i < bmp.Height; ++i) {
        for (int j = 0; j < bmp.Width; ++j) {
          Color col = bmp.GetPixel(j, i);
          data.Add(col.R);
          data.Add(col.G);
          data.Add(col.B);
          data.Add(col.A);
        }
      }

      storeName = storeName.Replace(".png", ".tex");
      byte[] dataArray = data.ToArray();
      int dataSize = dataArray.Length * Marshal.SizeOf(typeof(byte));
      IntPtr dataPtr = Marshal.AllocHGlobal(dataSize);
      Marshal.Copy(dataArray, 0, dataPtr, dataSize);

      if (pak_insert_data(pak, storeName, dataPtr, (uint)dataSize) == 0)
        Console.WriteLine("Converted and pak'd " + storeName + " successfully.");
      else
        Console.WriteLine("SOMETHING WENT WRONG!");

      Marshal.FreeHGlobal(dataPtr);
      return new Point(width, height);
    }

    public static void TraverseTreeAddingFiles(string root, List<string> fileList) {
      Stack<string> dirs = new Stack<string>(20);

      if (!System.IO.Directory.Exists(root)) {
        throw new ArgumentException();
      }
      dirs.Push(root);

      while (dirs.Count > 0) {
        string currentDir = dirs.Pop();
        string[] subDirs;
        try {
          subDirs = System.IO.Directory.GetDirectories(currentDir);
        }
        catch (UnauthorizedAccessException e) {
          Console.WriteLine(e.Message);
          continue;
        }
        catch (System.IO.DirectoryNotFoundException e) {
          Console.WriteLine(e.Message);
          continue;
        }

        string[] files = null;
        try {
          files = System.IO.Directory.GetFiles(currentDir);
        }

        catch (UnauthorizedAccessException e) {
          Console.WriteLine(e.Message);
          continue;
        }

        catch (System.IO.DirectoryNotFoundException e) {
          Console.WriteLine(e.Message);
          continue;
        }
        foreach (string file in files) {
          try {
            System.IO.FileInfo fi = new System.IO.FileInfo(file);
            if (fi.Name != "Thumbs.db")
              fileList.Add(fi.FullName);
          }
          catch (System.IO.FileNotFoundException e) {
            Console.WriteLine(e.Message);
            continue;
          }
        }
        foreach (string str in subDirs)
          dirs.Push(str);
      }
    }

    static void Main(string[] args) {
      List<string> files = new List<string>();
      if (args.Length != 2) {
        Console.WriteLine("Incorrect parameter count.");
        return;
      }
      string path = args[0];
      string pakFilename = args[1];
      path.Replace('/', '\\');
      if (!path.EndsWith("\\"))
        path += "\\";
      TraverseTreeAddingFiles(path, files);
      if (File.Exists(path))
        File.Delete(path);
      pak_create(pakFilename);
      IntPtr pak = pak_open(Path.GetFullPath(args[1]));
      Console.WriteLine("Pak'n files into " + pakFilename + "...");
      foreach (string file in files) {
        string storeName = file.Substring(file.IndexOf(path) + path.Length).Replace('\\', '/');
        // Convert tex/*.png into TEX format
        if (storeName.StartsWith("tex/") && storeName.EndsWith(".png")) {
          AddTextureToPak(file, storeName, pak);
        }

        // Convert spr/*.png to TEX format, creating a SPR file along the way
        else if (storeName.StartsWith("spr/") && storeName.EndsWith(".png")) {
          string storeName2 = string.Copy(storeName).Replace("spr/", "tex/").Replace(".png", ".tex");
          Point dims = AddTextureToPak(file, storeName2, pak);
          string spr = storeName2.Replace("tex/", "").Replace(".tex", "") + "\n0.5000\n0.5000\n" + dims.X.ToString() + "\n" + dims.Y.ToString() + "\n";
          Console.WriteLine(spr);
          byte[] bytes = System.Text.Encoding.UTF8.GetBytes(spr);

          storeName = storeName.Replace(".png", ".spr");
          int dataSize = bytes.Length * Marshal.SizeOf(typeof(byte));
          IntPtr dataPtr = Marshal.AllocHGlobal(dataSize);
          Marshal.Copy(bytes, 0, dataPtr, dataSize);

          if (pak_insert_data(pak, storeName, dataPtr, (uint)dataSize) == 0)
            Console.WriteLine("Converted and pak'd " + storeName + " successfully.");
          else
            Console.WriteLine("SOMETHING WENT WRONG!");

          Marshal.FreeHGlobal(dataPtr);
        }
        else {
          if (pak_insert(pak, file, storeName) == 0)
            Console.WriteLine("Pak'd " + storeName + " successfully.");
          else
            Console.WriteLine("SOMETHING WENT WRONG!");
        }
      }
      pak_close(pak);
    }
  }
}
