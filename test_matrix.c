#include "utest.h"
#include "matrix.h"

UTEST(matrix_create, simple) {
  matrix m = matrix_create(3, 5, 0.);
  ASSERT_TRUE(m.ok && m.n1==3 && m.n2==5);
}

UTEST(matrix_create, too_large) {
  matrix m = matrix_create((unsigned)-1, (unsigned)-1, 0.);
  ASSERT_FALSE(m.ok);
}

UTEST(matrix_create, zero) {
  matrix m = matrix_create(0, 0, 0.);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(matrix_identity, simple) {
  matrix m = matrix_identity(42);
  ASSERT_TRUE(m.ok && m.n1==42 && m.n2==42);
}

UTEST(matrix_identity, too_large) {
  matrix m = matrix_identity((unsigned) -1);
  ASSERT_TRUE(!m.ok);
}

UTEST(matrix_identity, zero) {
  matrix m = matrix_identity(0);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(scal_mul, simple) {
  matrix m = matrix_identity(2);
  matrix n = scal_mul(m, 3.);
  ASSERT_TRUE(n.ok && n.n1==2 && n.n2==2 && *matrix_get(n, 0,0)==3.);
}

UTEST(fast_pow, simple) {
  matrix m = matrix_identity(2);
  matrix m2 = scal_mul(m, 3.);
  matrix n = fast_pow(m2, 2);
  ASSERT_TRUE(n.ok && n.n1==2 && n.n2==2);
}
UTEST(fast_pow, complexiefied) {
  matrix m = matrix_identity(2);
  matrix m2 = scal_mul(m, 3.);
  matrix n = fast_pow(m2, 2);
  ASSERT_TRUE(*matrix_get(n, 1,1)==9.);
}

UTEST(matrix_destroy, simple) {
  matrix m = matrix_create(2, 5, 0.);
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_destroy, wrong) {
  matrix m;
  m.ok=false;
  m.data=(scalar*)0xdeadbeef;
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_get, simple) {
  matrix m = matrix_identity(12);
  ASSERT_TRUE(*matrix_get(m,3,3)==1.);
}

UTEST(matrix_get, wrong) {
  matrix m;
  m.ok=false;
  ASSERT_TRUE(matrix_get(m, 0, 0)==NULL);
}

UTEST_MAIN()  
