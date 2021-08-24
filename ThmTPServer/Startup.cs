//-----------------------------------------------------------------------------
// File Name   : Startup
// Author      : junlei
// Date        : 6/1/2021 1:44:24 PM
// Description : 
// Version     : 1.0.0      
// Updated     : 
//
//-----------------------------------------------------------------------------
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using ThmTPService.Services;

namespace ThmTPService {
    public class Startup {
        // This method gets called by the runtime. Use this method to add services to the container.
        // For more information on how to configure your application, visit https://go.microsoft.com/fwlink/?LinkID=398940
        public void ConfigureServices(IServiceCollection services) {
            services.AddGrpc();
            services.AddGrpcReflection();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env) {
            if (env.IsDevelopment()) {
                app.UseDeveloperExceptionPage();
            }

            // for compatibilities only (does not support HTTP/2)
            //AppContext.SetSwitch("Microsoft.AspNetCore.Server.Kestrel.EnableWindows81Http2", true);

            app.UseRouting();

            app.UseEndpoints(endpoints => {
                endpoints.MapGrpcService<GreeterService>();
                endpoints.MapGrpcService<ConnectionService>();
                endpoints.MapGrpcService<MarketDataService>();
                endpoints.MapGrpcService<OrderService>();

                if(env.IsDevelopment()) {
                    endpoints.MapGrpcReflectionService();
                }

                endpoints.MapGet("/", async context => {
                    await context.Response.WriteAsync("Communication with gRPC endpoints must be made through a gRPC client. To learn how to create a client, visit: https://go.microsoft.com/fwlink/?linkid=2086909");
                });
            });
        }
    }
}
