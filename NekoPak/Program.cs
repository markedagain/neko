/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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
    static extern int pak_insert_data(IntPtr pak, [MarshalAs(UnmanagedType.LPStr)] string filename, [MarshalAs(UnmanagedType.LPStr)] string nameInPak, IntPtr data, uint dataSize);

    [DllImport("neko.dll")]
    static extern int pak_close(IntPtr pak);

    public static void TraverseTreeAddingFiles(string root, List<string> fileList) {
      // Data structure to hold names of subfolders to be 
      // examined for files.
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
        // Perform the required action on each file here. 
        // Modify this block to perform your required task. 
        foreach (string file in files) {
          try {
            // Perform whatever action is required in your scenario.
            System.IO.FileInfo fi = new System.IO.FileInfo(file);
            //Console.WriteLine("{0}: {1}, {2}", fi.Name, fi.Length, fi.CreationTime);
            if (fi.Name != "Thumbs.db")
              fileList.Add(fi.FullName);
          }
          catch (System.IO.FileNotFoundException e) {
            // If file was deleted by a separate application 
            //  or thread since the call to TraverseTree() 
            // then just continue.
            Console.WriteLine(e.Message);
            continue;
          }
        }

        // Push the subdirectories onto the stack for traversal. 
        // This could also be done before handing the files. 
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
        if (storeName.EndsWith(".png")) {
          Bitmap bmp = (Bitmap)Image.FromFile(file);
          List<byte> data = new List<byte>();
          for (int i = 0; i < bmp.Height; ++i) {
            for (int j = 0; j < bmp.Width; ++j) {
              Color col = bmp.GetPixel(j, i);
              data.Add(col.R);
              data.Add(col.G);
              data.Add(col.B);
              data.Add(col.A);
            }
          }

          storeName.Replace(".png", ".tex");
          byte[] dataArray = data.ToArray();
          int dataSize = dataArray.Length * Marshal.SizeOf(typeof(byte));
          IntPtr dataPtr = Marshal.AllocHGlobal(dataSize);
          Marshal.Copy(dataArray, 0, dataPtr, dataSize);

          if (pak_insert_data(pak, file, storeName, dataPtr, (uint)dataSize) == 0)
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
