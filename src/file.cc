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

#include <regex>


namespace falkor {

bastian::Handle<File> File::Open(const std::string& uri, const std::string& mode) {
  bastian::Handle<File> file(NULL);
  std::regex uri_regex("^(\\w+)://(.+)$");
  std::smatch match;

  if (std::regex_match(uri, uri_regex)) {
    std::string protocol = match.str(1);
    std::string path = match.str(2);

    if (protocol == "bundle") {
      file = BundleFile::New(path);
      file.Open(mode);
    }
  }

  return file;
}


#ifdef FALKOR_ANDROID

bastian::Handle<File> BundleFile::New(const std::string& path) {
  bastian::Handle<File> handle(new AndroidBundleFile(path));
  return handle;
}

AndroidBundleFile::AndroidBundleFile(const std::string& path) : path_(path) {}

bool AndroidBundleFile::Open(const std::string& mode) {
  return false;
}

};
#endif


}  // namespace falkor