#include <stdio.h>
#include <stdarg.h>
#include <obstack.h>
#include <math.h> 
#include <stdbool.h>
#include <gmp.h>



void pollard_rho(const mpz_t N){
// B1. initialization
	mpz_t n, x, x_prime, k, l, g, dummy;

	mpz_init(n);
	mpz_init(x);
	mpz_init(x_prime);
	mpz_init(k);
	mpz_init(l);
	mpz_init(g);
	mpz_init(dummy);

	mpz_set(n, N);
	mpz_set_ui(x, 5);
	mpz_set_ui(x_prime, 2);
	mpz_set_ui(k, 1);
	mpz_set_ui(l, 1);
	mpz_set_ui(g, 1);
	int primality;	

// B2. Primality test
B2:	 
	primality = mpz_probab_prime_p(n,15);
	
	if(primality == 2){ // def prim
		gmp_printf("%Zd\n", n);
		return;
	}
	if(primality == 1){ // prob prime, up reps
		primality = mpz_probab_prime_p(n,50);
		if(primality == 2){
			gmp_printf("%Zd\n",n);
			return;
		}
	}

// B3. Factor found?
B3:
	// dummy = x' -x
	mpz_sub(dummy,x_prime,x);
	mpz_gcd(g,dummy, n);

	if(mpz_cmp_ui(g,1) == 0){
		goto B4;	
	}
	if(mpz_cmp(g,n) == 0){
		printf("failed");
		return;
	}
	gmp_printf("%Zd\n",g);

	mpz_fdiv_q(n,n,g);
	mpz_mod(x,x,n);
	mpz_mod(x_prime,x_prime,n);
	goto B2;	

// B4. Advance
B4:
	mpz_sub_ui(k,k,1);
	if(mpz_cmp_ui(k,0) == 0){
		mpz_set(x_prime, x);
		mpz_mul_ui(l,l,2);
		mpz_set(k,l);
	}	
	mpz_mul(dummy,x,x);
	mpz_add_ui(dummy,dummy,1);
	mpz_mod(x,dummy,n);
	goto B3;	
	
}
	


int main(int argc, char *argv[])
{

	if( argc == 2){
		mpz_t N;
		mpz_init(N);
		mpz_set_str(N, argv[1], 10);
		gmp_printf("Attempting to factor N = %Zd with Pollard rho algorithm from Knuth's Algorithm B in section 4.5.4 of TAOCP\n", N);
		pollard_rho(N);	
	}

return 0;
}
