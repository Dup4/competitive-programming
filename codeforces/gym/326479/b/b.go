package main

import (
	"bufio"
	"fmt"
	"os"
)

func run(n int64) (res int64) {
	if n < 10 {
		var f = [...]int64{0, -1, -1, 1, -1, 2, -1, 3, 1, 4, -1}
		return f[n]
	} else {
		var res, m int64
		n -= 2
		m = n / 4
		switch n % 4 {
		case 0:
			res = -1
		case 1:
			res = m*2 + 1
		case 2:
			res = m
		case 3:
			res = m*2 + 2
		}
		return res
	}
}

func pTable() {

	const N = 2000

	bf := func(n int) (res int) {
		for i := N; i > 1; i-- {
			for j := i - 1; j >= 1; j-- {
				if i*i-j*j == n {
					return j
				}
			}
		}
		return -1
	}

	for i := 1; i <= 1000; i++ {
		fmt.Println(i, bf(i))
	}
}

func main() {
	var T, n int64

	in, out := bufio.NewReader(os.Stdin), bufio.NewWriter(os.Stdout)

	defer out.Flush()

	// pTable()
	// return

	fmt.Fscan(in, &T)

	for ; T > 0; T-- {
		fmt.Fscan(in, &n)
		fmt.Fprintln(out, run(n))
	}
}

// x^2 = k^2 + n
// x^2 - k^2 = n
// (a + b)^2 = a^2 + 2ab + b^2 = a^2 + b(2a + b)
