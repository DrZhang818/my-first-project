$$
\begin{aligned}
\sum_{i=1}^{n}\sum_{j=1}^{n} ij[\gcd(i,j)=1]
&=\sum_i\sum_j\sum_{d|i,d|j}\mu(d)ij\\
&=\sum_{d=1}^n\mu(d)\left( \sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}i\cdot d \right)\left( \sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}j\cdot d \right)\\
&=\sum_{d=1}^{n}\mu(d)d^2\left[S\left(\left\lfloor \frac{n}{d} \right\rfloor\right)\right]^2
\end{aligned}
$$




$$
\begin{aligned}
\sum_{d = 1}^{\min(n,m)}\mu(d)\left( \sum_{x=1}^{\left\lfloor \frac{n}{d} \right\rfloor} \left\lfloor \frac{n}{xd} \right\rfloor \right)\left( \sum_{y=1}^{\left\lfloor \frac{m}{d} \right\rfloor} \left\lfloor \frac{m}{yd} \right\rfloor \right)

\end{aligned}
$$
