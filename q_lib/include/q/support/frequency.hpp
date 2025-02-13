/*=============================================================================
   Copyright (c) 2014-2022 Joel de Guzman. All rights reserved.

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(CYCFI_Q_FREQUENCY_HPP_FEBRUARY_21_2018)
#define CYCFI_Q_FREQUENCY_HPP_FEBRUARY_21_2018

#include <cstdint>
#include <cmath>
#include <q/support/base.hpp>
#include <q/support/value.hpp>

#if !defined(Q_DONT_USE_THREADS)
#include <chrono>
#include <thread>
#endif

namespace cycfi::q
{
   struct duration;
   struct frequency;
   struct period;

   ////////////////////////////////////////////////////////////////////////////
   struct frequency : value<double, frequency>
   {
      using base_type = value<double, frequency>;
      using base_type::base_type;

      constexpr explicit            frequency(double val) : base_type(val) {}

      constexpr explicit            frequency(duration d);

      [[deprecated("Use as_double(db) instead of double(db)")]]
      constexpr explicit operator   double() const   { return rep; }

      [[deprecated("Use as_float(db) instead of float(db)")]]
      constexpr explicit operator   float() const    { return rep; }

      constexpr q::period           period() const;
   };

   // Free functions
   constexpr double as_double(frequency f)
   {
      return f.rep;
   }

   constexpr float as_float(frequency f)
   {
      return f.rep;
   }

   ////////////////////////////////////////////////////////////////////////////
   struct duration : value<double, duration>
   {
      using base_type = value<double, duration>;
      using base_type::base_type;

      constexpr explicit            duration(double val) : base_type(val) {}

      [[deprecated("Use as_double(db) instead of double(db)")]]
      constexpr explicit operator   double() const   { return rep; }

      [[deprecated("Use as_float(db) instead of float(db)")]]
      constexpr explicit operator   float() const    { return rep; }
   };

   // Free functions
   constexpr double as_double(duration d)
   {
      return d.rep;
   }

   constexpr float as_float(duration d)
   {
      return d.rep;
   }

   ////////////////////////////////////////////////////////////////////////////
   struct period : duration
   {
      using duration::duration;

      constexpr explicit            period(duration d) : duration(d) {}
      constexpr explicit            period(frequency f) : duration(1.0 / f.rep) {}
   };

   ////////////////////////////////////////////////////////////////////////////
   constexpr frequency::frequency(duration d)
    : base_type(1.0 / d.rep)
   {}

   constexpr q::period frequency::period() const
   {
      return q::period{ 1.0 / rep };
   }

   ////////////////////////////////////////////////////////////////////////////
#if !defined(Q_DONT_USE_THREADS)
   inline void sleep(duration t)
   {
      std::this_thread::sleep_for(std::chrono::duration<double>(as_double(t)));
   }
#endif

}

#endif
