/*---------------------------------------------------------------------------**
**          Filename    : PSU.cs                                             **
**          Description : Contorl PSU module                                 **
**          Created on  :2019/12/12                                          **
**          Created by  : Joel Tsai                                          **
**         (C)Copyright Promise Technology Inc., 2019                        **
**                    All Rights  Reserved.                                  **
**---------------------------------------------------------------------------*/
using System;
using i2api;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Chip.Contrl
{
    public class PSU
    {
        private byte ENC_PSU_DEVICE_CNT = 0x03;
        public NCT7802 NCT7802_MID;
        public PSU()
        {
            uint data = 0, offset = 0;
            uint addr = NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR;
            NCT7802_MID = new NCT7802();
            NCT7802_MID.Chip_init(NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR);
#if false
            data = NCT7802_Constants.NCT7802Y_BANK_DATA_0;
            offset = NCT7802_Constants.NCT7802Y_BANK_DATA_0;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               //goto exit_error;
            }

            /* Diable monitoring operations */
            data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_STOP;
            offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = 0x2A;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SELECT_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            /* Enable GPIO 3,GPIO 4 */
            data = 0x0C;
            offset = NCT7802_Constants.NCT7802Y_GPIO_ENABLE_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = 0x00;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SEL_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_START;
            offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
                //goto exit_error;
            }

            //////////////////////////////////////////////////////////////
            ///
            data = 0x2A;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SELECT_REG;
            if (I2C_write_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
                //goto exit_error;
            }

            /* Enable GPIO 3,GPIO 4 */
            data = 0x0C;
            offset = NCT7802_Constants.NCT7802Y_GPIO_ENABLE_REG;
            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
               // goto exit_error;
            }

            data = 0x00;
            offset = NCT7802_Constants.NCT7802Y_GPIO_MODE_SEL_REG;
            if (I2C_write_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
              //  goto exit_error;
            }

            data = NCT7802_Constants.NCT7802Y_CONFIG_DATA_START;
            offset = NCT7802_Constants.NCT7802Y_CONFIG_START_REG;
            if (I2C_write_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
                //goto exit_error;
            }
#endif

            PSULEDinit();
            PSUFanSpeedInit();
        }

        private void PSULEDinit()
        {
            uint data = 0, addr = 0, offset = 0;


            data = NCT7802_Constants.NCT7802Y_PSU_LED_INIT;
            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_WRITE_PORT_1;

            if (I2C_write_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }

            data = NCT7802_Constants.NCT7802Y_PSU_LED_CONFIG_INIT;
            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_CONFIG_PORT_1;

            if (I2C_write_value(addr, offset, ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }
        }

        private void PSUFanSpeedInit()
        {
            uint data = 0, addr = 0, offset = 0, fanNum;


            for (fanNum = 0; fanNum < ENC_PSU_DEVICE_CNT; fanNum++)
            {
                    switch (fanNum)
                    {
                        case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                            offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                            break;
                        case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                            offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                            break;
                        default:
                            Console.WriteLine("PCH200 PSU fan number out of range.\n");
                            break;
                    }

                    data = PSU_Constants.ENC_A3340R_PSU_DEFAULT_FAN_SPEED;
                    if (I2C_write_value(addr, offset, ref data) == -1)
                    {
                     Console.WriteLine("PCH200 PSU I2C write fail.\n");
                    }

            }
        }
        public void Set_Fan(uint fanNum, uint level)
        {

        }

        public void Get_Temperature(ref uint?[] Temperature)//ref uint?[] Temperature)
        {
            uint status = 0, data = 0, addr = 0, offset = 0, bit = 0;
            for (uint tempNum = 0; tempNum < Temperature.Length; tempNum++)
            {
                PSUPresentStatus(tempNum, ref status);

                if (status == 0)
                {
                    Temperature[tempNum] = 0;
                    return;
                }

                switch (tempNum)
                {
                    case PCH_Constants.PCH200_I2C_PSU_TEMP_SENSOR_0:
                        addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                        offset = NCT7802_Constants.NCT7802Y_TEMP_RTD3_HIGH_REG;
                        break;

                    case PCH_Constants.PCH200_I2C_PSU_TEMP_SENSOR_1:
                        addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                        offset = NCT7802_Constants.NCT7802Y_TEMP_RTD2_HIGH_REG;
                        break;

                    default:
                        Console.WriteLine("PCH200 PSU device number out of range.\n");
                        break;
                }
                data = 0;
                if (I2C_read_value(addr, offset, ref data) == -1)
                {
                    //*temperature = temperature_prev[tempNum];
                    Console.WriteLine("PCH200 PSU I2C read fail.\n");
                    return;
                }
                data += 3;    //For Fitting Real temperature
                Temperature[tempNum] = data;
            }
            return;
        }

        public void PSUPresentStatus(uint psuNum, ref uint status)
        {
            uint data = 0, addr = 0, offset = 0, bit=0;

            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_READ_PORT_0;

            switch (psuNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    bit = NCT7802_Constants.NCT7802Y_GPIO5_MASK;
                    break;

                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    bit = NCT7802_Constants.NCT7802Y_GPIO4_MASK;
                    break;

                default:
                    Console.WriteLine("PCH200 PSU device number out of range.\n");
                    break;
            }
            if (I2C_read_value(addr, offset,ref data) == -1)
            {
               // *status = status_prev[psuNum];
                Console.WriteLine("PCH200 PSU I2C read fail.\n");
               // return;
            }

            if ((data & bit) == 0)
            {
                status = 1; /* present */
                //gEncPSUPresent[psuNum] = TRUE;
            }
            else
            {
                status = 0; /* not present */
                //gEncPSUPresent[psuNum] = FALSE;
            }

        }
        public void GetPSUFanSpeed(uint fanNum, ref uint fanSpeed)
        {
            uint data = 0, addr = 0, offset = 0, hdata = 0, ldata = 0, temp_data = 0;

            switch (fanNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                    offset = NCT7802_Constants.NCT7802Y_FAN_IN2_COUNT_REG;
                    break;
                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                    offset = NCT7802_Constants.NCT7802Y_FAN_IN1_COUNT_REG;
                    break;

                default:
                    Console.WriteLine("PCH200 PSU fan number out of range.\n");
                    break;
            }


            /* Get fan speed from PSU */
            hdata = 0;
            if (I2C_read_value(addr, offset,ref hdata) == -1)
            {
                //*fanSpeed = speed_prev[fanNum];
                Console.WriteLine("PCH200 PSU I2C read fail.\n");
                return;
            }

            ldata = 0;
            offset = NCT7802_Constants.NCT7802Y_FAN_LOW_COUNT_REG;
            if (I2C_read_value(addr, offset,ref ldata) == -1)
            {
               // *fanSpeed = speed_prev[fanNum];
                Console.WriteLine("PCH200 PSU I2C read fail.\n");
                return;
            }

            if ((hdata == 0xFF) && (ldata == 0xF8))
            {
                fanSpeed = 0;
            }
            else
            {
                temp_data = ((hdata << 5) | (ldata >> 3));
                fanSpeed = (temp_data >> 4);             
            }
            return;
        }

        public void SetPSUGlobeErr(uint  psuNum, uint status)
        {
            uint data = 0, addr = 0, offset = 0;//, hdata = 0, ldata = 0, temp_data = 0;
            uint bitR = 0, bitG = 0, bitmap = 0;//, LEDmap = 0; 
            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_WRITE_PORT_1;

            switch (psuNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    bitR = NCT7802_Constants.NCT7802Y_GPIO3_MASK;
                    bitG = NCT7802_Constants.NCT7802Y_GPIO4_MASK;
                    break;

                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    bitR = NCT7802_Constants.NCT7802Y_GPIO1_MASK;
                    bitG = NCT7802_Constants.NCT7802Y_GPIO2_MASK;
                    break;

                default:
                    Console.WriteLine("PCH200 PSU status number out of range.\n");
                    break;
            }

            if (I2C_read_value(addr, offset, ref bitmap) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }

            switch (status)
            {
                case PSU_Constants.ENC_LED_OFF:
                case PSU_Constants.ENC_LED_DARK:
                    bitmap &= ~bitG;
                    bitmap &= ~bitR;
                    break;

                case PSU_Constants.ENC_LED_RED:
                    bitmap &= ~bitG;
                    bitmap |= bitR;
                    break;

                case PSU_Constants.ENC_LED_GREEN:
                    bitmap &= ~bitR;
                    bitmap |= bitG;
                    break;

                case PSU_Constants.ENC_LED_AMBER:
                    bitmap |= bitR;
                    bitmap |= bitG;
                    break;

                default:
                    Console.WriteLine("PCH200 PSU status number out of range.\n");
                    break;
            }

            //LEDmap = bitmap;

            if (I2C_write_value(addr, offset, ref bitmap) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }
        }

        public void PSUSetFanSpeed(uint fanNum, uint speedlevel)
        {
            uint data = 0, addr = 0, offset = 0;
            if (speedlevel == PSU_Constants.ENC_PSU_FULL_FAN_SPEED)
                data = PSU_Constants.ENC_A3340R_PSU_FULL_FAN_SPEED;
            else if (speedlevel == PSU_Constants.ENC_PSU_DEFAULT_FAN_SPEED)
                data = PSU_Constants.ENC_A3340R_PSU_DEFAULT_FAN_SPEED;

            switch (fanNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL2_REG;
                    break;
                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_2;
                    offset = NCT7802_Constants.NCT7802Y_FAN_FANCTL1_REG;
                    break;
                default:
                    Console.WriteLine("PCH200 PSU fan number out of range.\n");
                    break;
            }
            if (I2C_write_value(addr, offset,ref data) != 0)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }
        }

        public void SetPSUOnOff(uint psuNum, uint status)
        {
            uint data = 0, addr = 0, offset = 0, selectbit = 0;

            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_WRITE_PORT_1;

            switch (psuNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    selectbit = NCT7802_Constants.NCT7802Y_GPIO6_MASK;
                    break;
                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    selectbit = NCT7802_Constants.NCT7802Y_GPIO5_MASK;
                    break;
                default:
                    break;
            }
            data = 0;
            if (I2C_read_value(addr, offset,ref data) == -1)
            {
                Console.WriteLine("PCH200 PSU I2C read fail.\n");
            }

            if (status==1) /* on */
            {
                data |= selectbit;
            }
            else if(status==0)/* off */
            {
                data &= ~selectbit;
            }
            else
            {
                return;
            }

            if (I2C_write_value(addr, offset,ref data) != 0)
            {
                Console.WriteLine("PCH200 PSU I2C write fail.\n");
            }

            return;
        }

        public int I2C_write_value(uint addr, uint reg, ref uint data)
        {
            // return pch200_smbus_write(addr, reg, PCH_BYTE_DATA, data, BLEN);
            uint[] data_temp = { data };
            return PCHSMBUS.WriteSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
        }

        public int I2C_read_value(uint addr, uint reg, ref uint data)
        {

            //return pch200_smbus_read(addr, reg, PCH_BYTE_DATA, data, BLEN);
            int ret;
            uint[] data_temp = { data };
            ret = PCHSMBUS.ReadSMB(addr, reg, NCT7802_Constants.BLEN, ref data_temp);
            data = data_temp[0];
            return ret;

        }

    }
}
