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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_LIST_BUCKETS_REQUEST_H_
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_LIST_BUCKETS_REQUEST_H_

#include "google/cloud/storage/bucket_metadata.h"
#include "google/cloud/storage/internal/http_response.h"
#include "google/cloud/storage/internal/request_parameters.h"
#include "google/cloud/storage/well_known_parameters.h"

namespace google {
namespace cloud {
namespace storage {
inline namespace STORAGE_CLIENT_NS {
namespace internal {
/**
 * Request the metadata for a bucket.
 */
class ListBucketsRequest
    : public GenericRequest<ListBucketsRequest, MaxResults, Prefix, Projection,
                            UserProject> {
 public:
  ListBucketsRequest() = default;
  explicit ListBucketsRequest(std::string project_id)
      : project_id_(std::move(project_id)) {}

  std::string const& project_id() const { return project_id_; }
  ListBucketsRequest& set_project_id(std::string project_id) {
    project_id_ = std::move(project_id);
    return *this;
  }

  std::string const& page_token() const { return page_token_; }
  ListBucketsRequest& set_page_token(std::string page_token) {
    page_token_ = std::move(page_token);
    return *this;
  }

 private:
  std::string project_id_;
  std::string page_token_;
};

std::ostream& operator<<(std::ostream& os, ListBucketsRequest const& r);

struct ListBucketsResponse {
  static ListBucketsResponse FromHttpResponse(HttpResponse&& response);

  std::string next_page_token;
  std::vector<BucketMetadata> items;
};

std::ostream& operator<<(std::ostream& os, ListBucketsResponse const& r);

}  // namespace internal
}  // namespace STORAGE_CLIENT_NS
}  // namespace storage
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_STORAGE_INTERNAL_LIST_BUCKETS_REQUEST_H_
