//-----------------------------------------------------------------------------
// File Name   : TimeUtil
// Author      : junlei
// Date        : 1/11/2020 11:15:14 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Globalization;

namespace ThmCommon.Utilities {
    public static class TimeUtil {
        public const string DatetimeMSFormat = "yyyy-MM-dd HH:mm:ss.fff"; // by millisecond

        public static string DateTime2MilliSecondsString(DateTime dt) {
            return dt.ToString(DatetimeMSFormat);
        }

        public static long CalcRoundTripTime(long timesent, long timerec) {
            return timerec - timesent;
        }

        //Get current time in milliseconds
        public static long StartRoundTripTest() {
            return DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
        }

        public static long TimeNow() {
            return DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
        }

        public static int TimeNowInt() {
            return (int)(DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond);
        }

        public static DateTime Seconds2DateTime(long secs) {
            DateTime dt = DateTime.MinValue;
            return dt.AddSeconds(secs);
        }

        public static DateTime MilliSeconds2DateTime(long milliSecs) {
            var posixTime = DateTime.SpecifyKind(new DateTime(1970, 1, 1), DateTimeKind.Local);
            return posixTime.AddMilliseconds(milliSecs);
        }

        public static DateTime NanoSeconds2DateTime(long nanoseconds) {
            return new DateTime(1970, 1, 1).AddTicks(nanoseconds / 100);
        }

        public static DateTime GetDTCTime(ulong nanoseconds) {
            DateTime pointOfReference = new DateTime(2000, 1, 1, 0, 0, 0, DateTimeKind.Utc);
            long ticks = (long)(nanoseconds / 100);
            return pointOfReference.AddTicks(ticks);
        }

        public static DateTime TimeOffset(long start_time, long offset) {
            TimeSpan time = TimeSpan.FromMilliseconds(start_time + offset);
            return new DateTime(1970, 1, 1) + time;
        }

        public static long NanoToMilli(long nanos) {
            return nanos / 1000000;
        }

        public static long MilliTime() {
            //return (long)(System.DateTime.Now.Subtract(new System.DateTime(1970, 1, 1))).TotalSeconds * 1000;
            return (long)DateTime.Now.Subtract(new DateTime(1970, 1, 1)).TotalMilliseconds;
        }

        public static int DateTimeToNanoLong(DateTime obj) {
            return (int)(obj.Ticks % TimeSpan.TicksPerMillisecond % 10) * 100;
        }

        // DatetimeMSFormat = "yyyy-MM-dd HH:mm:ss.fff"; 
        public static DateTime String2DateTime(string str, string format = "yyyyMMdd HH:mm:ss.fff") {
            //string iString = "2005-05-05 22:12:20 PM";
            return DateTime.ParseExact(str, format, CultureInfo.InvariantCulture);
        }

        // returns current time in UTC as microseconds
        public static long EpochTimeUtc(int offset_in_sec = 0) {
            return (long)((DateTime.UtcNow.AddSeconds(offset_in_sec) - new DateTime(1970, 1, 1)).TotalMilliseconds * 1000000);
        }
    }
}
