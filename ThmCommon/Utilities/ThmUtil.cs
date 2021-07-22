//-----------------------------------------------------------------------------
// File Name   : TimeUtil
// Author      : junlei
// Date        : 1/17/2020 11:02:26 AM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Net;
using System.Net.Mail;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;

namespace ThmCommon.Utilities {
    public static class ThmUtil {
        public static string GenerateGUID() {
            return Guid.NewGuid().ToString();
        }

        public static string[] EnumItems2Strings<T>() {
            return Enum.GetNames(typeof(T));
        }

        public static string Enum2String<T>(T type) {
            return Enum.GetName(typeof(T), type);
        }

        /*
        public static void PullMMOrders(OrderMsg orderMsg) {
            //check if MM threads are running
            bool hasMMRunning = InternalOrderBook.TriggerOrders.Keys.Select(t => t.Contains("MM_")).Any();
            bool MMOrderHit = orderMsg.orderTag.Contains("MM") && orderMsg.instrumentID.Contains("APEX");
            if (hasMMRunning && MMOrderHit)
            {
                //If this is a MM contract, pull the rest of the MM contracts
                Debug.WriteLine("Pulling Other APEX MM Orders");
                var existingMMOrders = InternalOrderBook.InternalBook.Values.Where(o => o.OrderStatus != "F" && (o.OrderStatus == "A" || o.OrderStatus == "U") && o.OrderID != null && o.OrderTag.Contains("MM"));

                foreach (UniversalOrder uo in existingMMOrders) {
                    Wrappers.UpdateOrder(uo.Provider, "C", uo, null);
                    //var t = Task.Delay(50);
                    //t.Wait();
                }

                foreach (var trigger_name in InternalOrderBook.TriggerOrders.Keys) {
                    if (trigger_name.Contains("MM_") && trigger_name.Contains("APEX")) {
                        InternalOrderBook.TriggerOrders[trigger_name].StopTrigger(true);
                    }
                }
            }
        }

        public static UniversalOrder FindOrSyncInternalOrder(UniversalOrder externalOrder) {
            List<UniversalOrder> seq = new List<UniversalOrder>();

            //external order MUST have order ID
            if (externalOrder.OrderID != null) {
                var now = Util.TimeNow();
                if (externalOrder.OrderStatus == "A") {
                    //ensure to sort by descending`
                    if (InternalOrderBook.InternalBook.ContainsKey(externalOrder.OrderID)) {
                        var res = InternalOrderBook.InternalBook[externalOrder.OrderID];
                        seq.Add(res);
                    }
                    else {
                        //if(InternalOrderBook.internal_book.Values.Any(o => o.GenerateInternalID().Equals(external_order.GenerateInternalID()) && !o.orderStatus.Equals("F")))

                        //needs to be 
                        seq = InternalOrderBook.InternalBook.Values.Where(o => o.GenerateInternalID() == externalOrder.GenerateInternalID()
                        && o.OrderTag == externalOrder.OrderTag
                        && (o.OrderStatus != "F" && o.OrderStatus != "PF")).OrderByDescending(o => o.SentTime).ToList();

                        if (seq.Count == 0 && externalOrder.OrderTag.Contains("TC"))
                        {
                            seq = InternalOrderBook.InternalBook.Values.Where(o => o.OrderTag != null && o.OrderTag == externalOrder.OrderTag
                            && (o.OrderStatus != "F" && o.OrderStatus != "PF")).ToList();
                        }
                    }

                    if (seq.Any()) {
                        var obj = seq.First();

                        if (!string.IsNullOrEmpty(obj.OrderTag)) //If autospreader had already been run and completed, the next time it is run, it will take that a similar instrument to be the exact same leg (filled or working) {
                            obj.OrderID = externalOrder.OrderID;
                            obj.OrderRef = externalOrder.OrderRef;
                            obj.EntryPrice = externalOrder.EntryPrice;
                            obj.OrderQty = externalOrder.OrderQty;
                            obj.OrderStatus = externalOrder.OrderStatus;
                            obj.RecTime = externalOrder.RecTime;
                            obj.OrderPurpose = externalOrder.OrderStatus;
                        }
                        else {
                        }
                        //else {
                        //    var res = InternalOrderBook.trigger_orders.Values.Where(t => t.triggerType.Equals(TriggerType.AutoSpread) 

                        //    && t.running == true && t.spread.leg_tracker.Values.Any(l => l.uo.providerInstrumentID.Equals(obj.providerInstrumentID)));

                        //    if(res.Count() > 0) {
                        //        var leg = res.First().spread.leg_tracker.Values.Where(l => l.uo.providerInstrumentID.Equals(obj.providerInstrumentID)).First();
                        //        obj.orderTag = leg.orderTag;
                        //        obj.legInfo = leg.legType;
                        //    }
                        //    else {
                        //        ("More than one spread found, need to deconflict");
                        //    }
                        //}

                        //if (external_order.orderID.Equals(obj.orderID)) { //taking the wrong ID probably, it should not exist!
                        //}
                        //else {
                        //    obj.orderID = external_order.orderID;
                        //}

                        //order tag and leg info are internal
                        //obj.orderTag = external_order.orderTag;
                        //obj.legInfo = external_order.legInfo;
                    
                        //update IOB from here

                        InternalOrderBook.ExternalBook.AddOrUpdate(obj.OrderID, obj, (key, oldValue) => obj);
                        //InternalOrderBook.internal_book.AddOrUpdate(obj.orderID, obj, (key, oldValue) => obj);

                        return obj;
                    }
                    else {
                        return null;
                    }
                }

                else if (externalOrder.OrderStatus == "T") { //This is a trade message
                    if (InternalOrderBook.InternalBook.ContainsKey(externalOrder.OrderID)) {
                        var res = InternalOrderBook.InternalBook[externalOrder.OrderID];
                        seq.Add(res);
                    }

                    if (seq.Any()) {
                        var obj = seq.First();
                        if (!string.IsNullOrEmpty(obj.OrderTag)) //If autospreader had already been run and completed, the next time it is run, it will take that a similar instrument to be the exact same leg (filled or working)
                        {
                            //get weighted avverage fill
                            double prev_cost = obj.FillPrice * obj.FillQty;
                            double new_cost = externalOrder.FillPrice * externalOrder.FillQty;
                            int newQty = obj.FillQty + externalOrder.FillQty;
                            double avg = (prev_cost + new_cost) / newQty;

                            if (Double.IsNaN(avg)) {
                                avg = externalOrder.FillPrice;
                            }

                            if (obj.OrderStatus != "A") {
                                obj.AverageFillPrice = avg;
                            }

                            obj.OrderID = externalOrder.OrderID;
                            obj.OrderRef = externalOrder.OrderRef;
                            obj.FillQty += externalOrder.FillQty;
                            obj.FillPrice = externalOrder.FillPrice;
                        }

                        InternalOrderBook.InternalBook.AddOrUpdate(obj.OrderID, obj, (key, oldValue) => obj);
                        InternalOrderBook.ExternalBook.AddOrUpdate(obj.OrderID, obj, (key, oldValue) => obj);
                        return obj;
                    }
                    else {
                        return null;
                    }
                }
                else {
                    seq = InternalOrderBook.InternalBook.Values.Where(o => (o.OrderID != null && o.OrderID == externalOrder.OrderID)).OrderBy(o => o.OrderRef).ToList();
                    if (seq.Any()) {
                        var obj = seq.First();
                        return obj;
                    }
                    else {
                        return null;
                    }
                }
            }
            else {
                return null;
            }
        }
        
        public static void UpdateTriggerOrOrderRowPrice(DataGridView workingOrdersGrid, string column, string orderTag, string newValue) {
            var rows = workingOrdersGrid.Rows.Cast<DataGridViewRow>();
            if (rows.Any()) { //else nothing to remove
                var potential_rows = rows.Where(r => r.Cells["OrderTag"].Value.ToString() == orderTag);
                // && r.Cells["OrderStatus"].Value.ToString().Equals("Working Trigger"));

                if (potential_rows.Any()) {
                    workingOrdersGrid.BeginInvoke(new MethodInvoker(delegate {                        
                        try { //find specific row
                            potential_rows.First().Cells[column].Value = newValue;
                        }
                        catch {
                            Debug.WriteLine("No more values to edit");
                        }
                    }));
                }

                workingOrdersGrid.EndEdit();
            }
        }
        */

        /// <summary>
        /// class type T MUST be marked as [Serializable] for this to work.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="obj"></param>
        /// <returns></returns>
        public static T DeepClone<T>(T obj) {
            using (var ms = new MemoryStream()) {
                var formatter = new BinaryFormatter();
                formatter.Serialize(ms, obj);
                ms.Position = 0;

                return (T)formatter.Deserialize(ms);
            }
        }

        /// <summary>
        /// copy properties for object
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <returns></returns>
        public static object CopyProperties(object from, object to) {
            if (from == null) {
                return null;
            }

            foreach (PropertyInfo propA in from.GetType().GetProperties()) {
                PropertyInfo propB = to.GetType().GetProperty(propA.Name);
                propB.SetValue(to, propA.GetValue(from, null), null);
            }
            return to;

            /*
            //get the list of all properties in the destination object
            var destProps = to.GetType().GetProperties();

            //get the list of all properties in the source object
            foreach (var sourceProp in from.GetType().GetProperties())
            {
                foreach (var destProperty in destProps)
                {
                    //if we find match between source & destination properties name, set
                    //the value to the destination property
                    if (destProperty.Name == sourceProp.Name
                        && destProperty.PropertyType.IsAssignableFrom(sourceProp.PropertyType))
                    {
                        destProperty.SetValue(destProps, 
                            sourceProp.GetValue(sourceProp, new object[] { }), 
                            new object[] { });
                        break;
                    }
                }
            }*/

            //return to;
        }

        public static void CopyList(List<string> from, List<string> to) {
            for (int i = 0; i < from.Count; i++) {
                to.Add(from[i]);
            }
        }

        //Give a list of contract code and year with its exchange e.g. FEF19-SGX, this function will populate the rest of the months
        public static List<string> GenerateInstrumentIDS(int from, List<string> codes) {
            List<string> output = new List<string>();

            foreach (string c in codes) {
                string[] strArr = c.Split('-');
                string contractYear = strArr[0];
                string exh = strArr[1];

                for (int month = from; month <= 12; month++) {
                    string pad = "0";

                    if (month < 10) {
                        pad += month;
                    }
                    else {
                        pad = "" + month;
                    }

                    output.Add(contractYear + pad + "-" + exh);
                }
            }
            return output;
        }

        //Converts from technical contract ID (ATP)'s FEF1905 to FEFMay19
        public static string SimplifyInstrumentID(string contractID, string provider) {
            contractID = contractID.Split('-')[0];
            int lenAdjust = 4;

            if (provider == "ATP") {
                string year_mo = contractID.Substring(Math.Max(0, contractID.Length - lenAdjust));

                int st = contractID.IndexOf(year_mo);
                int prod_en = contractID.Length - st;
                string product = contractID.Substring(0, st).Trim();
                string month = year_mo.Substring(2, 2);
                if (month.Substring(0, 1) == "0") {
                    month = month.Substring(1, 1);
                }
                string month_name = DateTimeFormatInfo.CurrentInfo.GetAbbreviatedMonthName(int.Parse(month));

                return product + month_name + year_mo.Substring(0, 2);
            }
            else if (provider == "TT") {
                return contractID;
            }

            return contractID;
        }

        //public static void PrintEssentialDepth(FieldsUpdatedEventArgs e) {
        //    Debug.WriteLine(DateTime.Now);
        //    Debug.WriteLine(e.Fields.Instrument.InstrumentDetails.Name);
        //    Debug.WriteLine("BestBid:" + e.Fields.GetBestBidPriceField().FormattedValue + "|" + e.Fields.GetBestBidQuantityField().FormattedValue);
        //    Debug.WriteLine("BestAsk:" + e.Fields.GetBestAskPriceField().FormattedValue + "|" + e.Fields.GetBestAskQuantityField().FormattedValue);

        //    Debug.WriteLine("ImpliedBid:" + e.Fields.GetDirectBidPriceField().FormattedValue + "|" + e.Fields.GetDirectBidQuantityField().FormattedValue);
        //    Debug.WriteLine("ImpliedAsk:" + e.Fields.GetDirectAskPriceField().FormattedValue + "|" + e.Fields.GetDirectAskQuantityField().FormattedValue);

        //    Debug.WriteLine("ImpliedBid:" + e.Fields.GetImpliedBidPriceField().FormattedValue + "|" + e.Fields.GetImpliedBidQuantityField().FormattedValue);
        //    Debug.WriteLine("ImpliedAsk:" + e.Fields.GetImpliedAskPriceField().FormattedValue + "|" + e.Fields.GetImpliedAskQuantityField().FormattedValue);
        //}


        // by now, no use
        public static void SendMail(string recipient, string subject, string body, string attachment) {
            var fromAddress = new MailAddress("leijun@themeinternationaltrading.com", "Logger");
            const string fromPassword = "";

            using (var smtp = new SmtpClient {
                Host = "smtp.gmail.com",
                Port = 587,
                EnableSsl = true,
                DeliveryMethod = SmtpDeliveryMethod.Network,
                UseDefaultCredentials = false,
                Credentials = new NetworkCredential(fromAddress.Address, fromPassword)
            }) {
                MailAddress toAddress = new MailAddress(recipient, "MasterLogger");
                using (var message = new MailMessage(fromAddress, toAddress) {
                    Subject = subject,
                    Body = body
                }) {
                    if (File.Exists(attachment)) {
                        message.Attachments.Add(new Attachment(attachment));
                    }
                    smtp.Send(message);
                }
            }
        }

        public static void SendNotif(string title, string body) {
            //Stream dataStream = null;
            //commented out due to long waiting time

            //WebRequest request = WebRequest.Create("https://api.pushbullet.com/v2/pushes");
            //request.Method = "POST";
            //request.Headers.Add("Authorization", "Bearer " + token);
            //request.ContentType = "application/json; charset=UTF-8";
            //string postData =
            //    "{\"type\": \"link\", \"title\": \"" + title + "\", \"body\": \"" + body + "\", \"url\": \"insert url here\"}";
            //byte[] byteArray = Encoding.UTF8.GetBytes(postData);
            //request.ContentLength = byteArray.Length;
            //dataStream = request.GetRequestStream();
            //dataStream.Write(byteArray, 0, byteArray.Length);
            //dataStream.Close();
        }
    }

    public class Pair<T, U> {
        public T First { get; set; }
        public U Second { get; set; }

        public Pair() { }
        public Pair(T first, U second) {
            First = first;
            Second = second;
        }
    };

    public class Triple<T, U, W> {
        public T First { get; set; }
        public U Second { get; set; }
        public W Third { get; set; }

        public Triple() { }
        public Triple(T first, U second, W third) {
            First = first;
            Second = second;
            Third = third;
        }

        public void Update(T first, U second, W third) {
            First = first;
            Second = second;
            Third = third;
        }
    };

    public class FixedSizeQueue<T> : ConcurrentQueue<T> {
        public int Size { get; private set; }

        public FixedSizeQueue(int size) {
            Size = size;
        }

        private readonly object _syncObject = new object();
        public new void Enqueue(T obj) {
            base.Enqueue(obj);
            lock (_syncObject) {
                while (base.Count > Size) {
                    base.TryDequeue(out T outObj);
                }
            }
        }
    }
}
