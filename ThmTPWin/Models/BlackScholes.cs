using System;

namespace ThmTPWin.Models {
    public class BlackScholes {
        /* The Black and Scholes (1973) Stock option formula
		 * C# Implementation
		 * uses the C# Math.PI field rather than a constant as in the C++ implementaion
		 * the value of Pi is 3.14159265358979323846
	
		 	S= Stock price
			X= Strike price
			T= Years to maturity
			r= Risk-free rate
			v= Volatility
		*/
        public static double OptPrice(string CallPutFlag, double S, double X,
            double T, double r, double v) {
            double d1 = (Math.Log(S / X) + (r + v * v / 2.0) * T) / (v * Math.Sqrt(T));
            double d2 = d1 - v * Math.Sqrt(T);

            double dBlackScholes = 0.0;
            if (CallPutFlag == "c") {
                dBlackScholes = S * CND(d1) - X * Math.Exp(-r * T) * CND(d2);
            }
            else if (CallPutFlag == "p") {
                dBlackScholes = X * Math.Exp(-r * T) * CND(-d2) - S * CND(-d1);
            }
            return dBlackScholes;
        }

        public static double CND(double X) {
            const double a1 = 0.31938153;
            const double a2 = -0.356563782;
            const double a3 = 1.781477937;
            const double a4 = -1.821255978;
            const double a5 = 1.330274429;
            double L = Math.Abs(X);
            double K = 1.0 / (1.0 + 0.2316419 * L);
            double dCND = 1.0 - 1.0 / Math.Sqrt(2 * Convert.ToDouble(Math.PI.ToString())) *
                Math.Exp(-L * L / 2.0) * (a1 * K + a2 * K * K + a3 * Math.Pow(K, 3.0) +
                a4 * Math.Pow(K, 4.0) + a5 * Math.Pow(K, 5.0));

            if (X < 0) {
                return 1.0 - dCND;
            }
            else {
                return dCND;
            }
        }
    }
}
