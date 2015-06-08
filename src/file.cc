// Copyright David Corticchiato
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.


#include "./file.h"

#include <cstdlib>
#include "re2/re2.h"
#include <iostream>

namespace falkor {

bastian::Handle<File> File::OpenURI(const std::string& uri, const std::string& mode) {
  bastian::Handle<File> file(NULL);
  std::string protocol;
  std::string path;

  if (RE2::FullMatch(uri, "^(\\w+)://(.+)$", &protocol, &path)) {
    if (protocol == "bundle") {
      bastian::Handle<File> new_file = BundleFile::New(path);
      if (new_file->Open(mode)) file = new_file;
    }
  }

  return file;
}


#ifdef FALKOR_ANDROID


bastian::Handle<File> BundleFile::New(const std::string& path) {
  bastian::Handle<File> file(new AndroidBundleFile(path));
  return file;
}

AAssetManager * AndroidBundleFile::asset_manager_ = NULL;

void AndroidBundleFile::SetAssetManager(AAssetManager * asset_manager) {
  asset_manager_ = asset_manager;
}

AndroidBundleFile::AndroidBundleFile(const std::string& path) : path_(path), asset_(NULL) {}

bool AndroidBundleFile::Open(const std::string& mode) {
  AAsset * asset = AAssetManager_open(asset_manager_, path_.c_str(), AASSET_MODE_UNKNOWN);

  if (asset == NULL) return false;

  asset_ = asset;
  return true;
}

std::string AndroidBundleFile::Read(int size) {
  if (asset_ == NULL) return "";

  char * buffer = (char *) malloc(size);
  std::string result;
  int read_bytes = AAsset_read(asset_, buffer, size);

  if (read_bytes > 0) {
    result += buffer;
  }

  free(buffer);
  return result;
}


#endif


}  // namespace falkor