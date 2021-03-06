/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BlobDictionary.h"

#include <assert.h>

namespace filamat {
    BlobDictionary::BlobDictionary() : mStorageSize(0) {
}

const std::string& BlobDictionary::getBlob(size_t index) const noexcept {
    assert(index < mBlobs.size());
    return mBlobs[index];
}

size_t BlobDictionary::getBlobCount() const {
    return mBlobs.size();
}

size_t BlobDictionary::getIndex(const std::string& s) const noexcept {
    if (mBlobIndices.find(s) == mBlobIndices.end()) {
        return SIZE_MAX;
    }
    return mBlobIndices.at(s);
}

size_t BlobDictionary::addBlob(const std::vector<uint32_t>& vblob) noexcept {
    std::string blob((char*) vblob.data(), vblob.size() * 4);
    auto iter = mBlobIndices.find(blob);
    if (iter != mBlobIndices.end()) {
        return iter->second;
    }
    mBlobIndices[blob] = mBlobs.size();
    mBlobs.push_back(std::move(blob));
    mStorageSize += blob.size();
    return mBlobs.size() - 1;
}

} // namespace filamat
