/**
 @file    phase_nodes1.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    Aug 4, 2017
 @brief   Brief description
 */

#ifndef XPP_OPT_INCLUDE_XPP_OPT_VARIABLES_PHASE_NODES_H_
#define XPP_OPT_INCLUDE_XPP_OPT_VARIABLES_PHASE_NODES_H_

#include <string>
#include <vector>

#include <xpp/opt/bound.h>

#include "node_values.h"

namespace xpp {
namespace opt {

class PhaseNodes : public NodeValues {
public:
  using ContactVector = std::vector<bool>;
  enum Type {Force, Motion} type_;


  PhaseNodes (const Node& initial_value,
              const ContactVector& contact_schedule,
              const VecDurations& phase_durations,
              Type type,
              const std::string& name,
              int n_polys_in_changing_phase);
  ~PhaseNodes();


  /** @brief called by contact schedule when variables are updated.
   *
   * Converts phase durations to specific polynomial durations.
   */
  void UpdateDurations(const VecDurations& phase_durations);


  virtual VecBound GetBounds () const override;

private:
  VecBound OverlayMotionBounds (VecBound bounds) const;
  VecBound OverlayForceBounds (VecBound bounds) const;

  PolyInfoVec BuildPolyInfos(const ContactVector& contact_schedule,
                             int n_polys_in_changing_phase,
                             Type type) const;
};

} /* namespace opt */
} /* namespace xpp */

#endif /* XPP_OPT_INCLUDE_XPP_OPT_VARIABLES_PHASE_NODES_H_ */
