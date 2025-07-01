//===- StandaloneDummyPattern.cpp --- A dummy pass
//------------------------------*-===//

#include "Dialect/StandaloneOps.h"
#include "Transforms/Passes.h"
#include "mlir/Dialect/Affine/Passes.h"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/AffineStructures.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/Utils.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/Builders.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include <optional>

using namespace mlir;

#define DEBUG_TYPE "standalone-dummy-pass"

namespace mlir {
namespace {

/// Pattern match for dummy CRL
/// replace "foo" with "crl"

/*
struct FooToDummyCrlPattern : public mlir::OpRewritePattern<Operation> {
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(Operation* op, PatternRewriter &rewriter) const override {
    if(!canBeReplaced(op)) {
      return failure();
    }

    // Create a new bar op with the same operands and result type
    auto newOp = rewriter.create<standalone::CrlOp>(
        op->getLoc(), op->getResults().getType(), op->getOperands());

    // Replace the original foo op with the new bar op
    rewriter.replaceOp(op, newOp->getResults());

    return success();
  }

  bool canBeReplaced(Operation* op) const {
    return (op->getDialect()->getNamespace() == "standalone");
  }
};
*/

struct FooToDummyCrlPattern : public RewritePattern  {

  FooToDummyCrlPattern(PatternBenefit benefit, MLIRContext *context)
      : RewritePattern(MatchAnyOpTypeTag(), benefit, context) {}
  LogicalResult matchAndRewrite(Operation* op, PatternRewriter &rewriter) const override {
   
    if(!canBeReplaced(op)) {
      return failure();
    }

    // Create a new bar op with the same operands and result type
    //auto newOp = rewriter.create<standalone::CrlOp>(
    //    op->getLoc(), op->getResults().getType(), op->getOperands());

    llvm::outs() << "replacement function match is triggered" << "\n";
    auto newOp = rewriter.create<standalone::CrlOp>(
        op->getLoc(), op->getResults().getType(), op->getOperands());

    // Replace the original foo op with the new bar op
    rewriter.replaceOp(op, newOp->getResults());

    return success();
  }

  bool canBeReplaced(Operation* op) const {
    //return false;
    //llvm::outs() << op->getDialect()->getNamespace() << "\n";
    return (op->getDialect()->getNamespace() == "standalone" && 
            !llvm::isa<standalone::CrlOp>(op));
  }
};

/// =========================================================
/// Dummy Pattern
/// =========================================================

/// A pass to perform loop tiling on all suitable loop nests of a Function.
struct StandaloneDummyPattern
    : public standalone::StandaloneDummyPassBase<StandaloneDummyPattern> {
  explicit StandaloneDummyPattern() {
    // TODO: add your pattern init code
    // this->data-field-1 = kDefaultTileSize / 1024;
  }

  void runOnOperation() override;
  // TODO: add your pattern data fields and methods
  // void getTileSizes(ArrayRef<AffineForOp> band,
  //                   SmallVectorImpl<unsigned> *tileSizes);
  // constexpr static unsigned kDefaultTileSize = 4;
  
};

void StandaloneDummyPattern::runOnOperation() {
  // TODO: add your customised pattern implementation

  func::FuncOp func = getOperation(); // You get a function op directly

  llvm::outs() << "Running StandaloneDummyPattern on function: " << func.getName() << "\n";

}

/// A pass to perform loop tiling on all suitable loop nests of a Function.
struct StandaloneDummyCRLTransformPattern
    : public standalone::StandaloneDummyPassBase<StandaloneDummyCRLTransformPattern> {
  explicit StandaloneDummyCRLTransformPattern() {
    // TODO: add your pattern init code
    // this->data-field-1 = kDefaultTileSize / 1024;
  }

  void runOnOperation() override;
  // TODO: add your pattern data fields and methods
  // void getTileSizes(ArrayRef<AffineForOp> band,
  //                   SmallVectorImpl<unsigned> *tileSizes);
  // constexpr static unsigned kDefaultTileSize = 4;
  
};

void StandaloneDummyCRLTransformPattern::runOnOperation() {
  // TODO: add your customised pattern implementation
  
  func::FuncOp func = getOperation(); // You get a function op directly
  llvm::outs() << "Running Dummy CRL replacement on function: " << func.getName() << "\n";

  MLIRContext *ctx = &getContext();
    RewritePatternSet patterns(ctx);
    patterns.add<FooToDummyCrlPattern>(1,ctx);

    if (failed(applyPatternsGreedily(func, std::move(patterns)))) {
      signalPassFailure();
    }
}


} // namespace



// bypass the implementation
std::unique_ptr<OperationPass<mlir::func::FuncOp>>
standalone::createStandaloneDummyPass() {
  return std::make_unique<StandaloneDummyPattern>();
}

// bypass the implementation
std::unique_ptr<OperationPass<mlir::func::FuncOp>>
standalone::createStandaloneDummyCRLTransform() {
  return std::make_unique<StandaloneDummyCRLTransformPattern>();
}

} // namespace mlir
