/**
 * Copyright 2015 Google Inc. All Rights Reserved.
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

#ifndef DEVTOOLS_CDBG_DEBUGLETS_JAVA_ARRAY_EXPRESSION_EVALUATOR_H_
#define DEVTOOLS_CDBG_DEBUGLETS_JAVA_ARRAY_EXPRESSION_EVALUATOR_H_

#include "common.h"
#include "expression_evaluator.h"

namespace devtools {
namespace cdbg {

class ArrayReader;

// Evaluates array indexer sub-expressions.
class ArrayExpressionEvaluator : public ExpressionEvaluator {
 public:
  ArrayExpressionEvaluator(
      std::unique_ptr<ExpressionEvaluator> source_array,
      std::unique_ptr<ExpressionEvaluator> source_index);

  ~ArrayExpressionEvaluator() override;

  bool Compile(
      ReadersFactory* readers_factory,
      FormatMessageModel* error_message) override;

  const JSignature& GetStaticType() const override { return return_type_; }

  Nullable<jvalue> GetStaticValue() const override { return nullptr; }

  ErrorOr<JVariant> Evaluate(
      const EvaluationContext& evaluation_context) const override;

 private:
  // Subexpression that computes the actual array object.
  std::unique_ptr<ExpressionEvaluator> source_array_;

  // Subexpression that computes the index of the array we are accessing.
  std::unique_ptr<ExpressionEvaluator> source_index_;

  // Array reader object.
  std::unique_ptr<ArrayReader> array_reader_;

  // Array element type.
  JSignature return_type_;

  DISALLOW_COPY_AND_ASSIGN(ArrayExpressionEvaluator);
};


}  // namespace cdbg
}  // namespace devtools

#endif  // DEVTOOLS_CDBG_DEBUGLETS_JAVA_ARRAY_EXPRESSION_EVALUATOR_H_


