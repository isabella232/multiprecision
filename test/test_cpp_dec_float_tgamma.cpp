///////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2021.
//  Copyright 2021 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//

#if !defined(TEST_CPP_BIN_FLOAT) && !defined(TEST_CPP_DEC_FLOAT)
#define TEST_CPP_DEC_FLOAT
#endif

#if defined(TEST_CPP_BIN_FLOAT) && defined(TEST_CPP_DEC_FLOAT)
#error Error: only one of either TEST_CPP_BIN_FLOAT or TEST_CPP_DEC_FLOAT can be defined at the same time.
#endif

#include <boost/detail/lightweight_test.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include "test.hpp"

#if defined(TEST_CPP_BIN_FLOAT)
#include <boost/multiprecision/cpp_bin_float.hpp>
#endif

#if defined(TEST_CPP_DEC_FLOAT)
#include <boost/multiprecision/cpp_dec_float.hpp>
#endif

template<class T>
void test()
{
   // N[Gamma[5/2], 120]
   const T control_tgamma_2_and_half("1.32934038817913702047362561250585888709816209209179034616035584238968346344327413603121299255390849906217011771821192800");

   // N[Gamma[500/2], 120]
   const T control_tgamma_2_fifty   ("1.29314250436364309292832582080974738839793748706951226669917697084512949902204448379552716614841127978037140294127577317E490");

   const T tgamma_2_and_half = boost::math::tgamma(T(T(5)   / 2));
   const T tgamma_2_fifty    = boost::math::tgamma(T(T(500) / 2));

   BOOST_CHECK_CLOSE_FRACTION(tgamma_2_and_half, control_tgamma_2_and_half, T(std::numeric_limits<T>::epsilon() * T(1.0E6)));
   BOOST_CHECK_CLOSE_FRACTION(tgamma_2_fifty   , control_tgamma_2_fifty,    T(std::numeric_limits<T>::epsilon() * T(1.0E6)));
}

int main()
{
  #if defined(TEST_CPP_BIN_FLOAT)
   using big_float_type_016 = boost::multiprecision::number<boost::multiprecision::cpp_bin_float<(std::max)(std::numeric_limits<double>::digits + 1, 16)>>;
   using big_float_type_035 = boost::multiprecision::number<boost::multiprecision::cpp_bin_float<(std::max)(std::numeric_limits<double>::digits + 1, 35)>>;
   using big_float_type_105 = boost::multiprecision::number<boost::multiprecision::cpp_bin_float<105>>;
  #endif

  #if defined(TEST_CPP_DEC_FLOAT)
   using big_float_type_016 = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<(std::max)(std::numeric_limits<double>::digits + 1, 16)>>;
   using big_float_type_035 = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<(std::max)(std::numeric_limits<double>::digits + 1, 35)>>;
   using big_float_type_105 = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<105>>;
  #endif

   test<big_float_type_016>();
   test<big_float_type_035>();
   test<big_float_type_105>();

   return boost::report_errors();
}
