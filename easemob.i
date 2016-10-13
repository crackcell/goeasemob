%module easemob
%{
#include "easemobclient.h"
%}

%include <typemaps.i>
%include "std_string.i"
%include "std_vector.i"

namespace std {
  %template(StringVector) vector<string>;
}

#include "easemobclient.h"
