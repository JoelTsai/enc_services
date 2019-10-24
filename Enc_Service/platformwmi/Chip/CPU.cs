/*---------------------------------------------------------------------------**
**          Filename    : CPU.cs                                             **
**          Description : Get CPU status                                     **
**          Created on  :2019/07/15                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/

using WingRing;



namespace Chip.Contrl
{
    static class CPU_IA32_Constants
    {
        internal const uint IA32_THERM_STATUS = 0x19C;
        internal const uint MSR_TEMPERATURE_TARGET = 0x1A2;
    }


    public class CPU
    {
        /*follow PCI spec define smbus device and funtion*/    
        public CPU()
        {
            //init CPU

        }

        private bool GET_TJMAX(ref uint tjmax)
        {
            uint eax = 0, edx = 0;

            Ring0.RdMsr(CPU_IA32_Constants.MSR_TEMPERATURE_TARGET, ref eax, ref edx);
           // Console.WriteLine("eax={0:x},edx={1:x}", eax, edx);
            tjmax = (eax & 0xFF0000)>>16;
            //Console.WriteLine("result={0:x}", temp);
            return true;

        }

        private bool GET_THERM_STATUS(ref uint therm)
        {
            //Digital Readout
            uint eax = 0, edx = 0;

            Ring0.RdMsr(CPU_IA32_Constants.IA32_THERM_STATUS, ref eax, ref edx);
            therm = (eax & 0x7F0000) >> 16;

            return true;

        }

        public void GetCPUTEMP(ref uint?[] CPU_temp)
        {
            uint tjmax = 0, therm = 0;
            //uint CPU_temp;
            GET_TJMAX(ref tjmax);
            GET_THERM_STATUS(ref therm);
            CPU_temp[0] = tjmax - therm;
            //Console.WriteLine("result={0}", CPU_temp[0]);
        }
      
    }
}