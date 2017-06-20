//===- DebugSymbolRVASubsection.h -------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_DEBUGINFO_CODEVIEW_DEBUGSYMBOLRVASUBSECTION_H
#define LLVM_DEBUGINFO_CODEVIEW_DEBUGSYMBOLRVASUBSECTION_H

#include "llvm/DebugInfo/CodeView/DebugSubsection.h"
#include "llvm/Support/BinaryStreamArray.h"
#include "llvm/Support/BinaryStreamReader.h"
#include "llvm/Support/Error.h"

namespace llvm {
namespace codeview {

class DebugSymbolRVASubsectionRef final : public DebugSubsectionRef {
public:
  typedef FixedStreamArray<support::ulittle32_t> ArrayType;

  DebugSymbolRVASubsectionRef();

  static bool classof(const DebugSubsectionRef *S) {
    return S->kind() == DebugSubsectionKind::CoffSymbolRVA;
  }

  ArrayType::Iterator begin() const { return RVAs.begin(); }
  ArrayType::Iterator end() const { return RVAs.end(); }

  Error initialize(BinaryStreamReader &Reader);

private:
  ArrayType RVAs;
};

class DebugSymbolRVASubsection final : public DebugSubsection {
public:
  DebugSymbolRVASubsection();

  static bool classof(const DebugSubsection *S) {
    return S->kind() == DebugSubsectionKind::CoffSymbolRVA;
  }

  Error commit(BinaryStreamWriter &Writer) const override;
  uint32_t calculateSerializedSize() const override;

  void addRVA(uint32_t RVA) { RVAs.push_back(support::ulittle32_t(RVA)); }

private:
  std::vector<support::ulittle32_t> RVAs;
};
} // namespace codeview
} // namespace llvm

#endif
