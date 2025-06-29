//===-- Passes.td - GPU pass definition file ---------------*- tablegen -*-===//
// Copyright 2023 Enflame Revolutionary Academy
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef STANDALONE_PASSES
#define STANDALONE_PASSES

include "mlir/Pass/PassBase.td"

// --------------------------------------------------------------------------
// Dummy Passes
// --------------------------------------------------------------------------


def StandaloneDummyPass : Pass<"standalone-dummy-pass", "mlir::func::FuncOp"> {
  let summary = "Dummy pass boilerplate";
  let constructor = "mlir::standalone::createStandaloneDummyPass()";
  let options = [
    Option<"optionName", "option-name", "uint64_t", /*default=*/"512",
           "Set the option for in KiB (default: 512)">,
  ];
  let dependentDialects = ["StandaloneDialect"];
}

def StandaloneDummyCRLTransform : Pass<"standalone-dummy-crl", "mlir::func::FuncOp"> {
  let summary = "dummy pass replace a node with CRL node";
  let constructor = "mlir::standalone::createStandaloneDummyCRLTransform()";
  let options = [
    //Option<"optionName", "option-name", "uint64_t", /*default=*/"512",
    //       "Set the option for in KiB (default: 512)">,
  ];
  let dependentDialects = ["StandaloneDialect",
                           "linalg::LinalgDialect"];
}


#endif // STANDALONE_PASSES
