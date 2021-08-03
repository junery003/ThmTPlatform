using Grpc.Core;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;

namespace ThmTPService.Services {
    public class OrderService : Order.OrderBase {
        private readonly ILogger<OrderService> _logger;
        public OrderService(ILogger<OrderService> logger) {
            _logger = logger;
        }

        public override Task<SendOrderRsp> SendOrder(SendOrderReq req, ServerCallContext context) {
            return Task.FromResult(new SendOrderRsp {
            });
        }

        public override Task<UpdateOrderRsp> UpdateOrder(UpdateOrderReq req, ServerCallContext context) {
            return Task.FromResult(new UpdateOrderRsp {
            });
        }

        public override Task<DeleteOrderRsp> DeleteOrder(DeleteOrderReq req, ServerCallContext context) {
            return Task.FromResult(new DeleteOrderRsp {
            });
        }
    }
}
