%module easemob
%{
#include "easemob_client.h"
%}

%include <typemaps.i>
%include "std_string.i"
%include "std_vector.i"

namespace std {
  %template(StringVector) vector<string>;
}

#include "easemob_client.h"
