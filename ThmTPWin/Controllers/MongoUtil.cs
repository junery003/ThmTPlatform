//-----------------------------------------------------------------------------
// File Name   : MongoUtil
// Author      : junlei
// Date        : 03/18/2021 5:03:20 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------

using MongoDB.Bson;
using MongoDB.Driver;

namespace ThmTPWin.Controllers {
    internal static class MongoUtil {
        //"mongodb://localhost:27017";
        private const string SERVER = "mongodb+srv://super_user:super_user1@cluster0.w5wrh.mongodb.net/myFirstDatabase?retryWrites=true&w=majority";

        internal static bool Auth(string userID, string pwd) {
            var client = new MongoClient(SERVER);
            var db = client.GetDatabase("ThemeTP");
            var collec = db.GetCollection<BsonDocument>("Users");

            var list = collec.Find(new BsonDocument("UserID", userID)).ToList();
            if (list.Count != 1) {
                return false;
            }

            return list[0]["Password"] == pwd;
        }
    }
}
