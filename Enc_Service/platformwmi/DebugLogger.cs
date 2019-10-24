using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security;
using System.Security.Permissions;
using System.Text;

namespace Enc_Service.platformwmi
{
    class DebugLogger
    {
        private static bool Enabled = false;
        private static string loggerPath;

        // Disable the logger
        public static void Disable()
        {
            DebugLogger.loggerPath = null;
            DebugLogger.Enabled = false;
        }

        public static void LoadConfiguration()
        {
            DebugLogger.Disable();

            using (RegistryKey localKey = RegistryKey.OpenBaseKey(Microsoft.Win32.RegistryHive.LocalMachine, RegistryView.Registry64))
            {
                using (RegistryKey softwareKey = localKey.OpenSubKey("SOFTWARE\\Pro_HWMonitor", true))
                {
                    if (softwareKey == null)
                    {
                        return;
                    }

                    object value = softwareKey.GetValue("DebugLogger");
                    if (value != null)
                    {
                        if (Directory.Exists((string)value))
                        {
                            DebugLogger.loggerPath = (string)value;
                            DebugLogger.Enabled = true;
                        }
                        else
                        {
                            Console.WriteLine("Invaild directory specified in registry");
                        }
                    }
                }
            }
        }

        public static void WriteLine(string message)
        {
            if (!DebugLogger.Enabled)
            {
                return;
            }
            
            string fullName = Path.Combine(DebugLogger.loggerPath, "HWMonitor.log");
            using (StreamWriter file = new StreamWriter(fullName, true))
            {
                file.WriteLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + " > " + message);
            }
        }
    }
}
