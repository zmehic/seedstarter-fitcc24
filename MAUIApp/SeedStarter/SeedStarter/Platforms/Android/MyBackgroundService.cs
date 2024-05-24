using Android;
using Android.App;
using Android.Content;
using Android.Content.Res;
using Android.OS;
using Android.Runtime;
using AndroidX.Core.App;
using FireSharp.Config;
using FireSharp.Interfaces;
using FireSharp.Response;
using SeedStarter.Data;


namespace SeedStarter.Platforms.Android
{
    [Service]
    internal class MyBackgroundService:Service
    {
        



        Timer timer = null;
        int myId = (new object()).GetHashCode();
        int BadgeNumber = 0;
        bool Started = false;
        
        public override IBinder OnBind(Intent intent)
        {
            return null;
        }

        public override StartCommandResult OnStartCommand(Intent intent, [GeneratedEnum] StartCommandFlags flags, int startId)
        {
            DateTime now = DateTime.Now;
            DateTime midnight = now.Date.AddDays(1);
            TimeSpan delay = midnight - now;

            var input = intent.GetStringExtra("inputExtra");

            var notificationIntent = new Intent(this, typeof(MainActivity));
            var pendingIntent = PendingIntent.GetActivity(this, 0, notificationIntent, PendingIntentFlags.Immutable);
            var notification = new NotificationCompat.Builder(this, MainApplication.ChannelId).SetContentText(input).
                SetContentIntent(pendingIntent);


            
            timer = new Timer(Timer_Elapsed, notification, (int)delay.TotalMilliseconds, (int)TimeSpan.FromHours(1).TotalMilliseconds);

           
            return StartCommandResult.Sticky;
        }

        void Timer_Elapsed(object state)
        {
            IFirebaseConfig config = new FirebaseConfig()
            {
                AuthSecret = "9kYvaeMdIRNFA0WmoNqyCv4rBapIGyCDOptrQIyF",
                BasePath = "https://seedstarter-f9b21-default-rtdb.europe-west1.firebasedatabase.app/"
            };

            IFirebaseClient client = new FireSharp.FirebaseClient(config);


            var tempVal =  client.Get("Status/Temperature");
            var humidityVal =  client.Get("Status/Humidity");
            var soilHumidityVal =  client.Get("Status/GroundHumidity");

            var setter = client.Push("Hourly", new
            {
                Temp=tempVal,
                Humidity=humidityVal,
                SoilHumidity=soilHumidityVal,
                DateTime=DateTime.Now
            });

            AndroidServiceManager.IsRunning = true;
            BadgeNumber++;

            //string timeString = $"Time: {DateTime.Now.ToLongTimeString()}";
            //var notification = (NotificationCompat.Builder)state;
            //notification.SetNumber(BadgeNumber);
            //notification.SetContentTitle(timeString);
            //StartForeground(myId,notification.Build());
        }
    }
}
