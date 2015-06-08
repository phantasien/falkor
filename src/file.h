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

#ifndef FALKOR_FILE_H_
#define FALKOR_FILE_H_

#include <string>
#include <bastian.h>

#ifdef FALKOR_ANDROID
#include <android/asset_manager.h>
#endif

namespace falkor {


class File {
 public:
  static bastian::Handle<File> OpenURI(const std::string& uri, const std::string& mode);
  virtual bool Open(const std::string& mode) = 0;
  virtual std::string Read(int size) = 0;
};


class BundleFile : public File {
 public:
  static bastian::Handle<File> New(const std::string& path);
};


#ifdef FALKOR_ANDROID
class AndroidBundleFile : public BundleFile {
  public:
    explicit AndroidBundleFile(const std::string& path);
    bool Open(const std::string& mode);
    std::string Read(int size);

    static void SetAssetManager(AAssetManager* asset_manager);

  private:
    std::string path_;
    AAsset * asset_;
    static AAssetManager* asset_manager_;
};
#endif


}  // namespace falkor

#endif  // FALKOR_FILE_H_