using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
using System.Reflection;
using static System.Net.Mime.MediaTypeNames;

namespace ConsoleApp1
{

    [StructLayout(LayoutKind.Sequential)]
    public struct TcpClient
    {
        public const int BUFF_SIZE = 1024;
    }

    internal class Program
    {

        private const string dllPath = @"C:\Users\79085\source\repos\cpp_study\Native_Library\x64\Debug\ExportLibrary.dll";

        [DllImport(dllPath)]
        public static extern void Run();

        public void Process ()
        {
            while (true)
            {
                if (Console.)
            }
        }

        static void Main(string[] args)
        {

            Run();
            Console.ReadKey();
        }
    }
}
