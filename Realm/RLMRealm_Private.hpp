////////////////////////////////////////////////////////////////////////////
//
// Copyright 2014 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#import "RLMRealm_Private.h"
#import "RLMUtil.hpp"
#import "shared_realm.hpp"

#import <realm/group.hpp>
#import <unordered_map>

namespace realm {
    class Group;
    class Realm;
    typedef std::shared_ptr<realm::Realm> SharedRealm;
}

struct RLMObjectInfo;

namespace std {
template<> struct hash<NSString *> {
    size_t operator()(__unsafe_unretained NSString *const str) const {
        return [str hash];
    }
};
}

class RLMSchemaInfo {
    using impl = std::unordered_map<NSString *, RLMObjectInfo>;
public:
    RLMObjectInfo *find(NSString *name) const noexcept;
    RLMObjectInfo& operator[](NSString *name) const; // throws

    impl::iterator begin();
    impl::iterator end();
    impl::const_iterator begin() const;
    impl::const_iterator end() const;
private:
    std::unordered_map<NSString *, RLMObjectInfo> m_objects;
};

@interface RLMRealm () {
    @public
    realm::SharedRealm _realm;
    RLMSchemaInfo _info;
}

// FIXME - group should not be exposed
@property (nonatomic, readonly) realm::Group *group;
@end
