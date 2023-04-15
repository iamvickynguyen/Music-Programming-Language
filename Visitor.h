#pragma once

#include "antlr4-runtime.h"
#include "libs/SynthtaxParserBaseVisitor.h"
#include "libs/SynthtaxParserVisitor.h"
#include <sstream>
#include <string>

namespace synthtax_antlr {
class Visitor : public SynthtaxParserBaseVisitor {
public:
	std::stringstream outfile;

  Visitor() {}

  std::any visitProg(SynthtaxParser::ProgContext *ctx) {
		outfile << "#include <builtin.h>\n";
		if (ctx->cppHeader() != nullptr)
			visitCppHeader(ctx->cppHeader());
		
		for (auto &f: ctx->function()) {
			visitFunction(f);
		}

		return NULL;
  }
  
	std::any visitCppHeader(SynthtaxParser::CppHeaderContext *ctx) {
		std::string header = ctx->getText();
		std::string start = "@header";
		std::string end = "@end_header";
		outfile << header.substr(start.length(), header.length() - start.length() - end.length()) << '\n';
    return visitChildren(ctx);
  }

  std::any
  visitFunction(SynthtaxParser::FunctionContext *ctx) {
    visitFuncDeclaration(ctx->funcDeclaration());
//		visitFuncBody(ctx->funcBody());
		return NULL;
  }

  std::any
  visitFuncDeclaration(SynthtaxParser::FuncDeclarationContext *ctx) {
		print_type(ctx->TYPE()->getText());
    outfile << " " << ctx->ID()->getText() << "(";
	
		if (ctx->formalParameters() != nullptr)
			visitFormalParameters(ctx->formalParameters());
	
		outfile << ")";
		outfile << '\n'; // TEMP
		return visitChildren(ctx);
  }

  std::any
  visitFormalParameters(SynthtaxParser::FormalParametersContext *ctx) {
		if (ctx->ID().size() > 0) {
			print_type(ctx->TYPE()[0]->getText());
			outfile << " " << ctx->ID()[0]->getText();
		}

		for (int i = 1; i < ctx->ID().size(); ++i) {
			outfile << ", ";
			print_type(ctx->TYPE()[i]->getText());
			outfile << " " << ctx->ID()[i]->getText();
		}
		return NULL;
  }

  std::any
  visitFuncBody(SynthtaxParser::FuncBodyContext *ctx) {
		std::cout << "visit FuncBodyContext\n";
    return visitChildren(ctx);
  }
  
  std::any visitStatement(SynthtaxParser::StatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitVarDeclaration(SynthtaxParser::VarDeclarationContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitExpressionStatement(SynthtaxParser::ExpressionStatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitIfStatement(SynthtaxParser::IfStatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitWhileStatement(SynthtaxParser::WhileStatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitReturnStatement(SynthtaxParser::ReturnStatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitAssignmentStatement(SynthtaxParser::AssignmentStatementContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitBlock(SynthtaxParser::BlockContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitExpression(SynthtaxParser::ExpressionContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitLessExpression(SynthtaxParser::LessExpressionContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitAddSubExpression(SynthtaxParser::AddSubExpressionContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitMulDivExpression(SynthtaxParser::MulDivExpressionContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitAtom(SynthtaxParser::AtomContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitExpressionList(SynthtaxParser::ExpressionListContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitLiteral(SynthtaxParser::LiteralContext *ctx) {
    return visitChildren(ctx);
  }

private:
	void print_type(const std::string &type) {
		if (type == "string") outfile << "std::string";
		else outfile << type;
	}
};
} // namespace synthtax_antlr
