//-----------------------------------------------------------------------------
// File Name   : DbController
// Author      : junlei
// Date        : 1/11/2020 12:13:14 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using System.Data;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;

namespace ThmCommon.Database {
    /// <summary>
    /// database operations
    /// </summary>
    public sealed class DbController {
        public async Task<bool> InsertAsync(string connStr, string sql) {
            using (var conn = new MySqlConnection(connStr)) {
                using (var cmd = new MySqlCommand(sql, conn)) {
                    await conn.OpenAsync();
                    await cmd.ExecuteNonQueryAsync();
                    //conn.Open();
                    //cmd.ExecuteNonQuery();
                }
            }

            return true;
        }

        public async void Query(string connStr, string sql) {
            using (var conn = new MySqlConnection(connStr)) {
                using (var cmd = new MySqlCommand(sql, conn)) {
                    await conn.OpenAsync();
                    var rdr = await cmd.ExecuteReaderAsync();

                    while (rdr.Read()) {
                        //Console.WriteLine(rdr[0] + " -- " + rdr[1]);
                    }
                    rdr.Close();
                }
            }
        }

        public async Task<DataTable> Query2DataTable(string connStr, string sql) {
            using (var conn = new MySqlConnection(connStr)) {
                using (var cmd = new MySqlCommand(sql, conn)) {
                    await conn.OpenAsync();

                    DataTable dt = new DataTable();
                    await new MySqlDataAdapter(cmd).FillAsync(dt);

                    return dt;
                }
            }
        }

        void Select(string connStr) {
            using (MySqlConnection connect = new MySqlConnection(connStr))
            using (MySqlCommand cmd = new MySqlCommand()) {
                string commandLine = "SELECT * FROM Table WHERE active=1";

                commandLine = commandLine.Remove(commandLine.Length - 3);
                cmd.CommandText = commandLine;

                cmd.Connection = connect;
                cmd.Connection.Open();

                MySqlDataReader msdr = cmd.ExecuteReader();

                while (msdr.Read()) {
                    //Read data
                }
                msdr.Close();
                cmd.Connection.Close();
            }
        }

        long Intert(string connStr) {
            using (MySqlConnection connect = new MySqlConnection(connStr))
            using (MySqlCommand cmd = new MySqlCommand()) {

                cmd.Connection = connect;
                cmd.Connection.Open();

                string commandLine = @"INSERT INTO Table (id, weekday, start, end) VALUES" +
                    "(@ id, @weekday, @start, @end);";

                cmd.CommandText = commandLine;

                //cmd.Parameters.AddWithValue("@ id", item.babysitterid);
                //cmd.Parameters.AddWithValue("@weekday", item.weekday);
                //cmd.Parameters.AddWithValue("@start", new TimeSpan(item.starthour, item.startmin, 0));
                //cmd.Parameters.AddWithValue("@end", new TimeSpan(item.endhour, item.endmin, 0));

                cmd.ExecuteNonQuery();
                long id = cmd.LastInsertedId;
                cmd.Connection.Close();
                return id;
            }
        }

        void Delete(string connStr) {
            using (var connect = new MySqlConnection(connStr)) {
                using (MySqlCommand cmd = new MySqlCommand()) {
                    cmd.Connection = connect;
                    cmd.Connection.Open();

                    string commandLine = @"INSERT INTO Table (id, weekday, start, end) VALUES" +
                        "(@ id, @weekday, @start, @end);";

                    cmd.CommandText = commandLine;

                    //cmd.Parameters.AddWithValue("@ id", item.babysitterid);
                    //cmd.Parameters.AddWithValue("@weekday", item.weekday);
                    //cmd.Parameters.AddWithValue("@start", new TimeSpan(item.starthour, item.startmin, 0));
                    //cmd.Parameters.AddWithValue("@end", new TimeSpan(item.endhour, item.endmin, 0));

                    cmd.ExecuteNonQuery();
                    long id = cmd.LastInsertedId;
                    cmd.Connection.Close();
                }
            }
        }
    }
}
