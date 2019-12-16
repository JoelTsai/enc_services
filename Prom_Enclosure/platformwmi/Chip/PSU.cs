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
    internal struct PSU_status
    {
        public bool[] OPERATIONAL;
        public bool[] PRESENT;
       // public bool[] TEMP_OC;
        public PSU_status(uint var)
        {
            OPERATIONAL = new bool[var];
            PRESENT = new bool[var];
           // TEMP_OC = new bool[var];

            for (int i = 0; i < var; i++)
            {
                OPERATIONAL[i] = false;
                PRESENT[i] = false;
              //  TEMP_OC[i] = false;
            }
        } 

    };

    public class PSU
    {
        private byte ENC_PSU_DEVICE_CNT = 0x03;
        public NCT7802 NCT7802_MID;
        internal PSU_status Status = new PSU_status(PSU_Constants.PSU_NUM);
        public PSU()
        {
            uint data = 0, offset = 0;
            uint addr = NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR;
            NCT7802_MID = new NCT7802();
            NCT7802_MID.Chip_init(NCT7802_Constants.NCT7802Y_BP_MID_PLANE_HW_MONITOR_ADDR);
#if false // not necessary form FW code 
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


            for (fanNum = 0; fanNum < ENC_PSU_DEVICE_CNT-1; fanNum++)
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

        public void Get_Temperature(ref uint?[] Temperature)//ref uint?[] Temperature)
        {
            uint  data = 0, addr = 0, offset = 0, bit = 0;
            bool status;
            for (uint tempNum = 0; tempNum < Temperature.Length; tempNum++)
            {
                status = false;
                PSUPresentStatus(tempNum, ref status);

                if (status == false)
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

        public void PSUPresentStatus(uint psuNum, ref bool status)
        {
            uint data = 0, addr = 0, offset = 0, presentbit = 0, operationbit = 0;

            addr = NCT7802_Constants.NCT7802Y_POWER_MID_PLANE_ADDR_4;
            offset = NCT7802_Constants.PCA955A_READ_PORT_0;

            switch (psuNum)
            {
                case PCH_Constants.PCH200_I2C_DEV_PSU_0:
                    presentbit = NCT7802_Constants.NCT7802Y_GPIO5_MASK;
                    operationbit = NCT7802_Constants.NCT7802Y_GPIO2_MASK;
                    break;

                case PCH_Constants.PCH200_I2C_DEV_PSU_1:
                    presentbit = NCT7802_Constants.NCT7802Y_GPIO4_MASK;
                    operationbit = NCT7802_Constants.NCT7802Y_GPIO1_MASK;
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
            if (presentbit != 0)
            {
                if ((data & presentbit) == 0)
                {

                    if ((data & operationbit) == 0)
                    {

                        if (Status.PRESENT[psuNum] == false)
                        {

                          I2connection.SetEvent(I2connection_Events.EVT_CLASS_PSU,
                          I2connection_Events.EVT_CODE_PSU_INSTALLED_AND_TURNED_OFF,
                          psuNum);
                        }
                        else if (Status.PRESENT[psuNum] == true && Status.OPERATIONAL[psuNum]==true)
                        {
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_PSU,
                            I2connection_Events.EVT_CODE_PSU_OPERATIONAL_AND_TURNED_OFF,
                            psuNum);
                        }

                        Status.PRESENT[psuNum] = true;
                        Status.OPERATIONAL[psuNum] = false;

                    }
                    else
                    {
                        if (Status.PRESENT[psuNum] == false)
                        {

                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_PSU,
                            I2connection_Events.EVT_CODE_PSU_INSTALLED_AND_TURNED_ON,
                            psuNum);
                        }
                        else if (Status.PRESENT[psuNum] == true && Status.OPERATIONAL[psuNum]==false)
                        {
                            I2connection.SetEvent(I2connection_Events.EVT_CLASS_PSU,
                            I2connection_Events.EVT_CODE_PSU_OPERATIONAL_AND_TURNED_ON,
                            psuNum);
                        }


                        Status.PRESENT[psuNum] = true;
                        Status.OPERATIONAL[psuNum] = true;
                    }//gEncPSUPresent[psuNum] = TRUE;
                }
                else
                {
                    if (Status.PRESENT[psuNum] == true)
                    {
                        I2connection.SetEvent(I2connection_Events.EVT_CLASS_PSU,
                            I2connection_Events.EVT_CODE_PSU_REMOVED,
                            psuNum);

                        Status.PRESENT[psuNum] = false;
                        Status.OPERATIONAL[psuNum] = false;
                    }//status = false; /* not present */
                    //gEncPSUPresent[psuNum] = FALSE;
                }
            }
            else
            {
                Status.PRESENT[psuNum] = false;
                Status.OPERATIONAL[psuNum] = false;
            }

            status = Status.PRESENT[psuNum];
            return;
        }
        public void GetPSUFanSpeed(ref uint?[,] Fan)
        {
            uint fanSpeed = 0, addr = 0, offset = 0, hdata = 0, ldata = 0, temp_data = 0, fanNum=0;
            for (fanNum = 0; fanNum < PSU_Constants.PSU_NUM; fanNum++)
            {
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
                if (I2C_read_value(addr, offset, ref hdata) == -1)
                {
                    //*fanSpeed = speed_prev[fanNum];
                    Console.WriteLine("PCH200 PSU I2C read fail.\n");
                    return;
                }

                ldata = 0;
                offset = NCT7802_Constants.NCT7802Y_FAN_LOW_COUNT_REG;
                if (I2C_read_value(addr, offset, ref ldata) == -1)
                {
                    // *fanSpeed = speed_prev[fanNum];
                    Console.WriteLine("PCH200 PSU I2C read fail.\n");
                    return;
                }

                if ((hdata == 0xFF) && (ldata == 0xF8))
                {
                    fanSpeed = 0;
                    Fan[fanNum, 0] = Convert.ToUInt32(fanSpeed);
                    Fan[fanNum, 1] = Enclsoure.Enclsoure_Constants.FAN_NOT_INSTALLED;
                    break;
                }
                else
                {
                    temp_data = ((hdata << 5) | (ldata >> 3));
                    fanSpeed = (temp_data >> 4);
                }
                Fan[fanNum, 0] = Convert.ToUInt32(fanSpeed);
                Fan[fanNum, 1] = Enclsoure.Enclsoure_Constants.FAN_OPERATIONAL;
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

        public void PSU_thermal()
        {

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
