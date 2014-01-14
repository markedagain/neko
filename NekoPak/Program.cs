using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace NekoPak {
  class Program {

    [DllImport("neko.dll")]
    static extern int pak_create([MarshalAs(UnmanagedType.LPStr)] string filename);

    [DllImport("neko.dll")]
    static extern IntPtr pak_open([MarshalAs(UnmanagedType.LPStr)] string filename);

    [DllImport("neko.dll")]
    static extern int pak_insert(IntPtr pak, [MarshalAs(UnmanagedType.LPStr)] string filename, [MarshalAs(UnmanagedType.LPStr)] string nameInPak);

    [DllImport("neko.dll")]
    static extern int pak_close(IntPtr pak);

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
      try {
        foreach (string d in Directory.GetDirectories(args[0]))
          foreach (string f in Directory.GetFiles(d))
            files.Add(f);
      }
      catch (System.Exception e) {
        Console.WriteLine(e.Message);
      }
      try {
        foreach (string f in Directory.GetFiles(args[0]))
          files.Add(f);
      }
      catch (System.Exception e) {
        Console.WriteLine(e.Message);
      }
      if (File.Exists(path))
        File.Delete(path);
      pak_create(pakFilename);
      IntPtr pak = pak_open(Path.GetFullPath(args[1]));
      Console.WriteLine(pakFilename);
      foreach (string file in files) {
        string storeName = file.Substring(file.IndexOf(path) + path.Length).Replace('\\', '/');
        if (pak_insert(pak, file, storeName) == 0)
          Console.WriteLine("Added " + file + " successfully.");
        else
          Console.WriteLine("SOMETHING WENT WRONG!");
      }
      pak_close(pak);
    }
  }
}
