// Copyright 2018 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/iam_bindings.h"
#include <algorithm>
#include <iterator>

namespace google {
namespace cloud {

void IamBindings::AddMember(std::string const& role,
                            std::string const& member) {
  bindings_[role].insert(member);
}

void IamBindings::AddMembers(google::cloud::IamBinding const& iam_binding) {
  std::string const& role(iam_binding.role());
  std::set<std::string> const& members = iam_binding.members();

  bindings_[role].insert(members.begin(), members.end());
}

void IamBindings::AddMembers(std::string const& role,
                             std::set<std::string> const& members) {
  bindings_[role].insert(members.begin(), members.end());
}

void IamBindings::RemoveMember(std::string const& role,
                               std::string const& member) {
  auto it = bindings_.find(role);
  if (it == bindings_.end()) {
    return;
  }

  auto& members = it->second;
  auto member_loc = members.find(member);

  if (member_loc != members.end()) {
    members.erase(member_loc);
  }
}

void IamBindings::RemoveMembers(google::cloud::IamBinding const& iam_binding) {
  std::string const& role(iam_binding.role());
  std::set<std::string> const& members = iam_binding.members();

  auto it = bindings_.find(role);
  if (it == bindings_.end()) {
    return;
  }

  auto& binding_members = it->second;
  for (auto const& member : members) {
    auto member_loc = binding_members.find(member);
    if (member_loc != binding_members.end()) {
      binding_members.erase(member_loc);
    }
  }
}

void IamBindings::RemoveMembers(std::string const& role,
                                std::set<std::string> const& members) {
  auto it = bindings_.find(role);
  if (it == bindings_.end()) {
    return;
  }

  auto& binding_members = it->second;
  for (auto const& member : members) {
    auto member_loc = binding_members.find(member);
    if (member_loc != binding_members.end()) {
      binding_members.erase(member_loc);
    }
  }
}

}  // namespace cloud
}  // namespace google
