using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace SeedStarter.Data
{
    public class GlobalValues
    {
        public static System.Drawing.Color clrOn = System.Drawing.Color.FromArgb(0, 206, 209);
        public static System.Drawing.Color clrOff = System.Drawing.Color.FromArgb(128, 128, 128);

        public static System.Drawing.Color clrManual = clrOff;
        public static System.Drawing.Color clrAuto = clrOff;
        public static System.Drawing.Color clrSemiAuto = clrOff;

        public static bool Manual = true;
        public static bool Auto = false;
        public static bool SemiAuto = false;

        public static bool temp = false;
        public static bool light = false;
        public static bool water = false;
        public static bool mist = false;
        public static bool fan = false;

        int nestoMaloOvoOno=0;

        public static int statisticvalue;

        public static List<Crop> listaUsjeva { get; set; }

        public static SelectedCrop values = new SelectedCrop();
    }

    public class SelectedCrop
    {
        public string Name { get; set; } = "";
        public int Humidity { get; set; } = 0;
        public int SoilHumidity { get; set; } = 0;
        public int Temp { get; set; } = 0;
    }

    public class Crop
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Temp { get; set; }
        public int Humidity { get; set; }
        public int SoilHumidity { get; set; }
        public bool Selected { get; set; }
    }

}
