/* Copyright 2019 The JAX Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "jaxlib/cuda/cuda_prng_kernels.h"

#include "jaxlib/cuda/cuda_gpu_kernel_helpers.h"
#include "jaxlib/kernel_pybind11_helpers.h"
#include "include/pybind11/pybind11.h"

namespace jax {
namespace {

std::string BuildCudaThreeFry2x32Descriptor(std::int64_t n) {
  return PackDescriptorAsString(ThreeFry2x32Descriptor{n});
}
pybind11::dict Registrations() {
  pybind11::dict dict;
  dict["cuda_threefry2x32"] = EncapsulateFunction(CudaThreeFry2x32);
  return dict;
}

PYBIND11_MODULE(_cuda_prng, m) {
  m.def("registrations", &Registrations);
  m.def("threefry2x32_descriptor", [](std::int64_t n) {
    std::string result = BuildCudaThreeFry2x32Descriptor(n);
    return pybind11::bytes(result);
  });
}

}  // namespace
}  // namespace jax
