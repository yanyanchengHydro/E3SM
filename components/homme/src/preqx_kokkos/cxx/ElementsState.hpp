/********************************************************************************
 * HOMMEXX 1.0: Copyright of Sandia Corporation
 * This software is released under the BSD license
 * See the file 'COPYRIGHT' in the HOMMEXX/src/share/cxx directory
 *******************************************************************************/

#ifndef HOMMEXX_ELEMENTS_STATE_HPP
#define HOMMEXX_ELEMENTS_STATE_HPP

#include "Types.hpp"

namespace Homme {

class HybridVCoord;

/* Per element data - specific velocity, temperature, pressure, etc. */
class ElementsState {
public:
  // Velocity in lon lat basis
  ExecViewManaged<Scalar * [NUM_TIME_LEVELS][2][NP][NP][NUM_LEV]> m_v;
  // Temperature
  ExecViewManaged<Scalar * [NUM_TIME_LEVELS][NP][NP][NUM_LEV]> m_t;
  // dp ( it is dp/d\eta * delta(eta)), or pseudodensity
  ExecViewManaged<Scalar * [NUM_TIME_LEVELS][NP][NP][NUM_LEV]> m_dp3d;

  ExecViewManaged<Real * [NUM_TIME_LEVELS][NP][NP]> m_ps_v;

  ElementsState() = default;

  void init(const int num_elems);

  void random_init(const int num_elems, const int seed, const Real max_pressure = 1.0);
  void random_init(const int num_elems, const int seed, const Real max_pressure, const HybridVCoord& hvcoord);

  KOKKOS_INLINE_FUNCTION
  int num_elems() const { return m_num_elems; }

  // Fill the exec space views with data coming from F90 pointers
  void pull_from_f90_pointers(CF90Ptr& state_v,    CF90Ptr& state_t,
                              CF90Ptr& state_dp3d, CF90Ptr& state_ps_v);

  // Push the results from the exec space views to the F90 pointers
  void push_to_f90_pointers(F90Ptr& state_v, F90Ptr& state_t, F90Ptr& state_dp) const;

private:
  int m_num_elems;
};

} // Homme

#endif // HOMMEXX_ELEMENTS_STATE_HPP