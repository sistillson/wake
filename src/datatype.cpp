/*
 * Copyright 2019 SiFive, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You should have received a copy of LICENSE.Apache2 along with
 * this software. If not, you may obtain a copy at
 *
 *    https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "datatype.h"
#include "expr.h"
#include "symbol.h"
#include <iostream>

Sum::Sum(AST &&ast) : name(std::move(ast.name)), location(ast.location) {
  for (auto &x : ast.args)
    args.push_back(std::move(x.name));
}

void Sum::addConstructor(AST &&ast) {
  size_t nargs = ast.args.size();
  members.emplace_back(std::move(ast));
  Constructor &cons = members.back();
  cons.index = members.size()-1;

  cons.expr = std::unique_ptr<Expr>(new App(LOCATION,
    new VarRef(LOCATION, "_", 0, 0),
    new VarRef(LOCATION, "_", 0, 1)));
  for (size_t i = 0; i < nargs; ++i)
    cons.expr = std::unique_ptr<Expr>(new App(LOCATION,
      cons.expr.release(),
      new VarRef(LOCATION, "_", nargs-i, 0)));
}

bool AST::unify(TypeVar &out, const std::map<std::string, TypeVar*> &ids) {
  if (Lexer::isLower(name.c_str())) {
    auto it = ids.find(name);
    if (it == ids.end()) {
      std::cerr << "Unbound type variable at " << location.text() << std::endl;
      return false;
    } else {
      return out.unify(*it->second, &location);
    }
  } else { // upper or operator
    TypeVar cons(name.c_str(), args.size());
    bool ok = out.unify(cons);
    bool childok = true;
    if (ok) {
      for (size_t i = 0; i < args.size(); ++i) {
        childok = args[i].unify(out[i], ids) && childok;
        if (!args[i].tag.empty()) out.setTag(i, args[i].tag.c_str());
      }
    }
    return ok && childok;
  }
}

std::ostream & operator << (std::ostream &os, const AST &ast) {
  os << ast.name;
  for (auto &x : ast.args)
    os << " (" << x << ")";
  return os;
}
