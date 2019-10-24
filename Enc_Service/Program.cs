using System;
using System.ServiceProcess;
using System.IO;
using System.Management;
using System.Diagnostics;
using Enclsoure;
using Microsoft.Win32;
using System.Collections.Generic;
using System.Timers;
using System.Threading;

namespace Enc_Service
{
    static public class Program
    {
        public  static  EventLog Pro_Event_viewer = new EventLog();

        static void Main(string[] args)
        {
            if (args.Length != 0)
            {
                Enc_Service.TimeParameter = System.Text.RegularExpressions.Regex.Replace(args[0], "[^0-9]", "");
            }
            Pro_Event_viewer.Source = "Promise";
            Pro_Event_viewer.Log = "Promise_event";
            if (!(Directory.Exists(Log_File.LogPath)))
            {
                Directory.CreateDirectory(Log_File.LogPath);
            }
            Pro_Event_viewer.WriteEntry("project init!");
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[]
            {
                new Enc_Service()
            };
            ServiceBase.Run(ServicesToRun);
        }

    }
    static internal class Log_File
    {
        /// <summary>
        /// is there necessary???????????????
        /// </summary>
        public static string LogPath = @"C:\ProgramData\Promise\ServiceLog\";
        public static string LogName = "WMIServiceLog";
        public static string LogType = ".txt";
        public static int LogId = 0;
        public static string[] LogTime = new string[3];
        public static string[] LogFile = new string[3];
        public static string FilePath = LogPath + LogName + LogType;
        public static string FilePathTime;
        public static int LogSize = 50 * 1024 * 1024;


        static public void FileLog(string LogMessage)
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");

            if (FileExist.Length == 0)
            {
                LogId = FileExist.Length;
                LogTime[LogId] = DateTime.Now.ToString("_yyyyMMdd_hhmmss");
                LogFile[LogId] = LogName + LogTime[LogId] + LogType;
                FilePathTime = LogPath + LogFile[LogId];
                using (FileStream stream = new FileStream(FilePathTime, FileMode.Append))
                using (StreamWriter writer = new StreamWriter(stream))
                {
                    writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + ", Log file is create!");
                    writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + " , " + LogMessage);
                }
            }
            else
            {
                FilePathTime = LogPath + LogFile[LogId];
                using (FileStream stream = new FileStream(FilePathTime, FileMode.Append))
                using (StreamWriter writer = new StreamWriter(stream))
                {
                    writer.WriteLine($"{DateTime.Now.ToString("yyyyMMdd_hh:mm:ss")}" + " , " + LogMessage);
                    if (FileExist.Length == 3)
                    {
                        DelLogFile();
                    }
                    CheckLogSize();
                    writer.Close();
                }
            }
        }

        static internal void DelLogFile()
        {
            DirectoryInfo LogExist = new DirectoryInfo(LogPath);
            FileInfo[] FileExist = LogExist.GetFiles(LogName + "*");

            string DeleteFilePath = LogPath + Convert.ToString(FileExist[0]);

            File.Delete(DeleteFilePath);
        }

        static internal void CheckLogSize()
        {
            FileInfo filesize = new FileInfo(FilePathTime);
            if (filesize.Length >= LogSize)
            {
                LogId += 1;
                if (LogId == 3)
                {
                    LogId = 0;
                }
                LogTime[LogId] = DateTime.Now.ToString("_yyyyMMdd_hhmmss");
                LogFile[LogId] = LogName + LogTime[LogId] + LogType;
                FilePathTime = LogPath + LogFile[LogId];
            }
        }
    }
}
