// A Bison parser, made by GNU Bison 3.6.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "Parser.hxx"


// Unqualified %code blocks.
#line 107 "Parser.yxx"

    #include <string>
    #include <iostream>
    #include "ast.hpp"
    #include "Lexer.hpp"
    #undef yylex
    #define yylex lexer.yylex


RNode* create_binary_expression(RNode* op_ptr, RNode* left_expr_ptr, RNode* right_expr_ptr) {
    auto op = wrap<OperatorRNode>(op_ptr);
    auto left_expr = wrap<ExpressionRNode>(left_expr_ptr);
    auto right_expr = wrap<ExpressionRNode>(right_expr_ptr);
    return new BinaryExpressionRNode(op, left_expr, right_expr);
}

RNode* create_unary_expression(RNode* op_ptr, RNode* expr_ptr) {
    auto op = wrap<OperatorRNode>(op_ptr);
    auto expr = wrap<ExpressionRNode>(expr_ptr);
    return new UnaryExpressionRNode(op, expr);
}

ExpressionSequenceRNodeSPtr delimit_expression_sequence(RNode* seq_ptr,
                                                        RNode *opening_delimiter_ptr,
                                                        RNode *closing_delimiter_ptr) {
    auto seq = wrap<ExpressionSequenceRNode>(seq_ptr);
    auto opening_delimiter = wrap<DelimiterRNode>(opening_delimiter_ptr);
    auto closing_delimiter = wrap<DelimiterRNode>(closing_delimiter_ptr);
    seq -> set_delimiters(opening_delimiter, closing_delimiter);
    return seq;
}


#line 80 "Parser.cxx"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "Parser.yxx"
namespace rastr { namespace r { namespace parser {
#line 173 "Parser.cxx"

  /// Build a parser object.
  Parser::Parser (rastr::r::parser::Lexer& lexer_yyarg, rastr::ast::ProgramRNodeSPtr program_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      program (program_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 143 "Parser.yxx"
                                                                                { yyresult = 0; YYACCEPT; }
#line 641 "Parser.cxx"
    break;

  case 3:
#line 145 "Parser.yxx"
                                                                                { }
#line 647 "Parser.cxx"
    break;

  case 4:
#line 146 "Parser.yxx"
                                                                                {
                                                                                  program -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = nullptr;
                                                                                }
#line 656 "Parser.cxx"
    break;

  case 5:
#line 150 "Parser.yxx"
                                                                                {
                                                                                  program -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = nullptr;
                                                                                }
#line 665 "Parser.cxx"
    break;

  case 6:
#line 154 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = nullptr;
                                                                                }
#line 673 "Parser.cxx"
    break;

  case 7:
#line 157 "Parser.yxx"
                                                                                {
                                                                                  program -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = nullptr;
                                                                                }
#line 682 "Parser.cxx"
    break;

  case 8:
#line 161 "Parser.yxx"
                                                                                {
                                                                                }
#line 689 "Parser.cxx"
    break;

  case 9:
#line 165 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 695 "Parser.cxx"
    break;

  case 10:
#line 166 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 701 "Parser.cxx"
    break;

  case 11:
#line 167 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 707 "Parser.cxx"
    break;

  case 12:
#line 170 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 713 "Parser.cxx"
    break;

  case 13:
#line 171 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 719 "Parser.cxx"
    break;

  case 14:
#line 174 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 725 "Parser.cxx"
    break;

  case 15:
#line 175 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 731 "Parser.cxx"
    break;

  case 16:
#line 176 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 737 "Parser.cxx"
    break;

  case 17:
#line 177 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 743 "Parser.cxx"
    break;

  case 18:
#line 178 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 749 "Parser.cxx"
    break;

  case 19:
#line 179 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 755 "Parser.cxx"
    break;

  case 20:
#line 180 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 761 "Parser.cxx"
    break;

  case 21:
#line 181 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 767 "Parser.cxx"
    break;

  case 22:
#line 182 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> set_delimiters(opening_delimiter, closing_delimiter);
                                                                                  yylhs.value = block;
                                                                                  lexer.disable_eat_lines();
                                                                                }
#line 780 "Parser.cxx"
    break;

  case 23:
#line 190 "Parser.yxx"
                                                                                { yylhs.value = new GroupExpressionRNode(wrap<DelimiterRNode>(yystack_[2].value),
                                                                                                                wrap<ExpressionRNode>(yystack_[1].value),
                                                                                                                wrap<DelimiterRNode>(yystack_[0].value)); }
#line 788 "Parser.cxx"
    break;

  case 24:
#line 193 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 794 "Parser.cxx"
    break;

  case 25:
#line 194 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 800 "Parser.cxx"
    break;

  case 26:
#line 195 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 806 "Parser.cxx"
    break;

  case 27:
#line 196 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 812 "Parser.cxx"
    break;

  case 28:
#line 197 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 818 "Parser.cxx"
    break;

  case 29:
#line 198 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 824 "Parser.cxx"
    break;

  case 30:
#line 199 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 830 "Parser.cxx"
    break;

  case 31:
#line 200 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 836 "Parser.cxx"
    break;

  case 32:
#line 201 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 842 "Parser.cxx"
    break;

  case 33:
#line 202 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 848 "Parser.cxx"
    break;

  case 34:
#line 203 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 854 "Parser.cxx"
    break;

  case 35:
#line 204 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 860 "Parser.cxx"
    break;

  case 36:
#line 205 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 866 "Parser.cxx"
    break;

  case 37:
#line 206 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 872 "Parser.cxx"
    break;

  case 38:
#line 207 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 878 "Parser.cxx"
    break;

  case 39:
#line 208 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 884 "Parser.cxx"
    break;

  case 40:
#line 209 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 890 "Parser.cxx"
    break;

  case 41:
#line 210 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 896 "Parser.cxx"
    break;

  case 42:
#line 211 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 902 "Parser.cxx"
    break;

  case 43:
#line 212 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 908 "Parser.cxx"
    break;

  case 44:
#line 213 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 914 "Parser.cxx"
    break;

  case 45:
#line 214 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 920 "Parser.cxx"
    break;

  case 46:
#line 215 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 926 "Parser.cxx"
    break;

  case 47:
#line 216 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 932 "Parser.cxx"
    break;

  case 48:
#line 217 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 938 "Parser.cxx"
    break;

  case 49:
#line 218 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 944 "Parser.cxx"
    break;

  case 50:
#line 219 "Parser.yxx"
                                                                                {
                                                                                  auto keyword = wrap<KeywordRNode>(yystack_[5].value);
                                                                                  auto params = delimit_expression_sequence(yystack_[3].value, yystack_[4].value, yystack_[2].value);
                                                                                  auto body = wrap<ExpressionRNode>(yystack_[0].value);
                                                                                  yylhs.value = new FunctionDefinitionExpressionRNode(keyword, params, body);
                                                                                }
#line 955 "Parser.cxx"
    break;

  case 51:
#line 225 "Parser.yxx"
                                                                                {
                                                                                  auto target = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto args = delimit_expression_sequence(yystack_[1].value, yystack_[2].value, yystack_[0].value);
                                                                                  yylhs.value = new FunctionCallExpressionRNode(target, args);
                                                                                }
#line 965 "Parser.cxx"
    break;

  case 52:
#line 230 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                        wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                        wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 975 "Parser.cxx"
    break;

  case 53:
#line 235 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfElseConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[4].value),
                                                                                                                            wrap<ConditionRNode>(yystack_[3].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[2].value),
                                                                                                                            wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 987 "Parser.cxx"
    break;

  case 54:
#line 242 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new ForLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                  wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                  wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 997 "Parser.cxx"
    break;

  case 55:
#line 247 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new WhileLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                    wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                    wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 1007 "Parser.cxx"
    break;

  case 56:
#line 252 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new RepeatLoopExpressionRNode(wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                     wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 1016 "Parser.cxx"
    break;

  case 57:
#line 256 "Parser.yxx"
                                                                                {
                                                                                  auto expr = wrap<ExpressionRNode>(yystack_[4].value);
                                                                                  auto indices = delimit_expression_sequence(yystack_[2].value, yystack_[3].value, yystack_[1].value);
                                                                                  yylhs.value = new IndexingExpressionRNode(expr, indices);
                                                                                }
#line 1026 "Parser.cxx"
    break;

  case 58:
#line 261 "Parser.yxx"
                                                                                {
                                                                                  auto expr = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto indices = delimit_expression_sequence(yystack_[1].value, yystack_[2].value, yystack_[0].value);
                                                                                  yylhs.value = new IndexingExpressionRNode(expr, indices);
                                                                                }
#line 1036 "Parser.cxx"
    break;

  case 59:
#line 266 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1042 "Parser.cxx"
    break;

  case 60:
#line 267 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1048 "Parser.cxx"
    break;

  case 61:
#line 268 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1054 "Parser.cxx"
    break;

  case 62:
#line 269 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1060 "Parser.cxx"
    break;

  case 63:
#line 270 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1066 "Parser.cxx"
    break;

  case 64:
#line 271 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1072 "Parser.cxx"
    break;

  case 65:
#line 272 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1078 "Parser.cxx"
    break;

  case 66:
#line 273 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1084 "Parser.cxx"
    break;

  case 67:
#line 274 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1090 "Parser.cxx"
    break;

  case 68:
#line 275 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1096 "Parser.cxx"
    break;

  case 69:
#line 276 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1102 "Parser.cxx"
    break;

  case 70:
#line 277 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1108 "Parser.cxx"
    break;

  case 71:
#line 278 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value;  }
#line 1114 "Parser.cxx"
    break;

  case 72:
#line 279 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1120 "Parser.cxx"
    break;

  case 73:
#line 282 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1132 "Parser.cxx"
    break;

  case 74:
#line 291 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1144 "Parser.cxx"
    break;

  case 75:
#line 300 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[4].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<ExpressionRNode>(yystack_[1].value);
                                                                                  auto keyword = wrap<KeywordRNode>(yystack_[2].value);
                                                                                  auto sym = wrap<SymbolExpressionRNode>(yystack_[3].value);
                                                                                  auto condition = std::make_shared<InRNode>(sym, keyword, expr);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, condition, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1159 "Parser.cxx"
    break;

  case 76:
#line 312 "Parser.yxx"
                                                                                { yylhs.value = new BlockExpressionRNode(); }
#line 1165 "Parser.cxx"
    break;

  case 77:
#line 313 "Parser.yxx"
                                                                                {
                                                                                  auto block = new BlockExpressionRNode();
                                                                                  block -> append_expression(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1175 "Parser.cxx"
    break;

  case 78:
#line 318 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<BlockExpressionRNode*>(yystack_[2].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  block -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1186 "Parser.cxx"
    break;

  case 79:
#line 324 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> append_delimiter(delimiter);
                                                                                  yylhs.value = block;
                                                                                }
#line 1197 "Parser.cxx"
    break;

  case 80:
#line 330 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<BlockExpressionRNode*>(yystack_[2].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  block -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1208 "Parser.cxx"
    break;

  case 81:
#line 336 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> append_delimiter(delimiter);
                                                                                  yylhs.value = block;
                                                                                }
#line 1219 "Parser.cxx"
    break;

  case 82:
#line 344 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  seq -> append_expression(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1229 "Parser.cxx"
    break;

  case 83:
#line 349 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[3].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  seq -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1240 "Parser.cxx"
    break;

  case 84:
#line 357 "Parser.yxx"
                                                                                { yylhs.value = new MissingExpressionRNode(); }
#line 1246 "Parser.cxx"
    break;

  case 85:
#line 358 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1252 "Parser.cxx"
    break;

  case 86:
#line 359 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1258 "Parser.cxx"
    break;

  case 87:
#line 360 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1264 "Parser.cxx"
    break;

  case 88:
#line 361 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1270 "Parser.cxx"
    break;

  case 89:
#line 362 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1276 "Parser.cxx"
    break;

  case 90:
#line 363 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1282 "Parser.cxx"
    break;

  case 91:
#line 364 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1288 "Parser.cxx"
    break;

  case 92:
#line 367 "Parser.yxx"
                                                                                { yylhs.value = new ExpressionSequenceRNode(); }
#line 1294 "Parser.cxx"
    break;

  case 93:
#line 368 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1300 "Parser.cxx"
    break;

  case 94:
#line 371 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  seq -> append_expression(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1311 "Parser.cxx"
    break;

  case 95:
#line 377 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  seq -> append_expression(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1322 "Parser.cxx"
    break;

  case 96:
#line 383 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[2].value);
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  seq -> append(delimiter, element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1334 "Parser.cxx"
    break;

  case 97:
#line 390 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[4].value);
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[3].value);
                                                                                  seq -> append(delimiter, element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1346 "Parser.cxx"
    break;

  case 98:
#line 399 "Parser.yxx"
    { lexer.enable_eat_lines(); }
#line 1352 "Parser.cxx"
    break;


#line 1356 "Parser.cxx"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -52;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     409,   409,   409,   409,   409,     0,   -52,   -52,   -52,   -52,
     -52,   -52,    50,     6,     8,    38,    41,   -52,   -52,   409,
     409,   409,   409,   409,    74,   -23,   131,    91,    23,   -23,
      86,   327,   327,    -9,    -8,     1,    12,     9,    80,   409,
     409,   409,   409,   409,    77,    18,    18,   241,    77,   -52,
     409,   409,   443,   409,   409,   443,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   443,    21,    22,   409,   409,   -52,
     -52,   -52,   409,   409,   -52,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,    81,    88,   -52,    76,    77,    27,   131,   -11,
      28,    77,    77,    77,   -22,    82,   -18,    48,   111,   -52,
     131,   198,   115,   342,   342,   342,   342,   342,   342,   327,
     284,   327,   284,    13,    13,   241,    18,   116,   116,    18,
     153,   118,   -52,   -52,   -52,   -52,   -23,   -23,   -23,   -23,
     409,   -52,   103,   409,   -52,   409,   409,   -52,   409,   409,
     409,   -52,   114,   121,   -52,    48,   409,   102,    30,   -52,
      77,    48,    48,    48,   443,   -52,    77,   409,   -52,   -52,
      48
  };

  const signed char
  Parser::yydefact_[] =
  {
       3,     0,    76,     0,     0,    18,    17,    14,    15,    16,
      19,    20,    21,     0,     0,     0,     0,    71,    72,     0,
       0,     0,     0,     0,     0,     4,     9,     0,     0,    77,
       0,    26,    27,     0,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,    56,    24,    25,    28,    29,     1,
       0,     0,    84,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    84,     0,     0,     8,     6,     2,
      23,    22,    81,    79,    62,    61,    66,    65,    60,    59,
      64,    63,    94,     0,    93,     0,    54,     0,    12,    52,
       0,    55,    10,    11,    18,    20,    21,    85,    98,    82,
      48,    49,    98,    43,    42,    38,    39,    40,    41,    44,
      45,    46,    47,    32,    31,    37,    30,    33,    34,    35,
      36,    98,    68,    67,    70,    69,     7,     5,    80,    78,
       0,    98,     0,     0,    74,     0,     0,    73,    88,    90,
      86,    51,     0,     0,    58,    95,     0,    96,     0,    13,
      53,    89,    91,    87,    84,    57,    50,     0,    75,    83,
      97
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -52,   -52,    71,   -32,    -3,   -52,   -52,   -52,   -52,   -51,
     -36,   -52,   -52,   -52,   -12
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,    24,    25,   107,    26,    43,    41,    39,    30,   108,
     109,    93,    27,    94,   152
  };

  const short
  Parser::yytable_[] =
  {
      31,    32,    50,   148,   112,    84,    86,   150,    97,    37,
     100,    38,    85,    87,    50,    88,    52,    45,    46,    47,
     146,    52,    89,   131,    33,    34,    90,    80,    35,    36,
      92,   144,   147,    91,   168,   132,   134,    98,    51,    98,
      55,    40,   133,   135,    42,    55,    33,    34,    50,    98,
     110,   111,    98,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    98,    28,    29,    49,    69,    70,    71,    72,    73,
      74,    75,    76,    72,    51,    74,    75,    76,   145,   145,
      44,   145,   141,    81,    48,    82,    35,    36,    83,   142,
      77,    95,    50,    78,    79,   143,   140,   149,   155,   145,
      96,   158,    99,   159,   101,   151,   161,   162,   163,    52,
     153,   102,   103,   154,   157,   164,   165,   167,   169,   156,
       0,     0,     0,     0,    52,   170,     0,    98,     0,     0,
      98,     0,    98,    55,     0,    98,    98,    98,   136,   137,
       0,     0,     0,   138,   139,    53,    52,    54,    55,     0,
       0,    98,     0,     0,    98,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,     0,    69,     0,
      55,    72,    73,    74,    75,    76,     0,     0,     0,    66,
      67,    68,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,   160,    72,     0,
      74,    75,    76,     0,     0,    55,     0,   166,     0,     0,
       0,     0,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,    67,    68,     0,
      69,    70,    71,    72,    73,    74,    75,    76,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    66,
      67,     0,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    55,     0,     0,     0,     0,     0,     0,     0,     0,
      56,    57,    58,    59,    60,    61,    62,     0,    64,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,     0,    52,    69,    70,    71,    72,
      73,    74,    75,    76,    55,     0,     0,     0,     0,     0,
       0,     0,     0,    56,    57,    58,    59,    60,    61,    55,
       0,     0,     0,     0,     0,     0,     0,     0,    -1,    -1,
      -1,    -1,    -1,    -1,     0,    66,    67,     0,     0,    69,
      70,    71,    72,    73,    74,    75,    76,     0,     0,     0,
      66,    67,     0,     0,    69,    70,    71,    72,    73,    74,
      75,    76,     1,     0,     0,     2,     0,     3,     0,     4,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,    14,     0,    15,
       0,    16,    17,    18,    19,     0,     1,     0,     0,     2,
       0,     3,     0,     4,     0,     0,     0,   104,     6,     7,
       8,     9,    10,   105,   106,    13,     0,    20,    21,    22,
      23,    14,     0,    15,     0,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,    21,    22,    23
  };

  const short
  Parser::yycheck_[] =
  {
       3,     4,    25,    25,    55,    14,    14,    25,    40,     3,
      42,     3,    21,    21,    25,    14,     3,    20,    21,    22,
      31,     3,    21,    74,    46,    47,    14,     4,    46,    47,
      21,     4,     4,    21,     4,    14,    14,    40,    61,    42,
      27,     3,    21,    21,     3,    27,    46,    47,    25,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     1,     2,     0,    62,    63,    64,    65,    66,
      67,    68,    69,    65,    61,    67,    68,    69,    61,    61,
      19,    61,     4,     7,    23,     9,    46,    47,    12,    11,
       9,    21,    25,    12,    13,    29,    25,    25,   140,    61,
      39,   143,    41,   145,    43,     4,   148,   149,   150,     3,
       5,    50,    51,     5,    21,    11,     5,    25,   164,   141,
      -1,    -1,    -1,    -1,     3,   167,    -1,   140,    -1,    -1,
     143,    -1,   145,    27,    -1,   148,   149,   150,    77,    78,
      -1,    -1,    -1,    82,    83,    24,     3,    26,    27,    -1,
      -1,   164,    -1,    -1,   167,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    62,    -1,
      27,    65,    66,    67,    68,    69,    -1,    -1,    -1,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,   146,    65,    -1,
      67,    68,    69,    -1,    -1,    27,    -1,   156,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    -1,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    -1,     3,    62,    63,    64,    65,
      66,    67,    68,    69,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    39,    40,    41,    -1,    58,    59,    -1,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
      58,    59,    -1,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,     3,    -1,    -1,     6,    -1,     8,    -1,    10,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,    32,    33,    34,    35,    -1,     3,    -1,    -1,     6,
      -1,     8,    -1,    10,    -1,    -1,    -1,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    58,    59,    60,
      61,    28,    -1,    30,    -1,    32,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     6,     8,    10,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    28,    30,    32,    33,    34,    35,
      58,    59,    60,    61,    77,    78,    80,    88,    78,    78,
      84,    80,    80,    46,    47,    46,    47,     3,     3,    83,
       3,    82,     3,    81,    78,    80,    80,    80,    78,     0,
      25,    61,     3,    24,    26,    27,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    58,    59,    60,    62,
      63,    64,    65,    66,    67,    68,    69,     9,    12,    13,
       4,     7,     9,    12,    14,    21,    14,    21,    14,    21,
      14,    21,    21,    87,    89,    21,    78,    79,    80,    78,
      79,    78,    78,    78,    14,    20,    21,    79,    85,    86,
      80,    80,    85,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    85,    14,    21,    14,    21,    78,    78,    78,    78,
      25,     4,    11,    29,     4,    61,    31,     4,    25,    25,
      25,     4,    90,     5,     5,    79,    90,    21,    79,    79,
      78,    79,    79,    79,    11,     5,    78,    25,     4,    86,
      79
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    76,    77,    88,    88,    88,    88,    88,    88,    78,
      78,    78,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    83,    84,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    86,    86,    86,    86,
      86,    86,    87,    87,    89,    89,    89,    89,    90
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     0,     1,     3,     2,     3,     2,     1,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     4,     3,     5,     3,     3,     2,     5,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     3,     3,     5,     0,     1,     3,     2,
       3,     2,     1,     4,     0,     1,     2,     3,     2,     3,
       2,     3,     0,     1,     1,     3,     3,     5,     0
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "LPAREN", "RPAREN",
  "RSQPAREN", "LBRACE", "RBRACE", "EXCLAMATION", "NEWLINE",
  "DOUBLE_EXCLAMATION", "COMMA", "SEMICOLON", "END_OF_INPUT", "STR_CONST",
  "LITERAL_CONST", "INT_CONST", "FLOAT_CONST", "COMPLEX_CONST",
  "RAW_STRING_CONST", "NULL_CONST", "SYMBOL", "FUNCTION",
  "INCOMPLETE_STRING", "LEFT_ASSIGN", "EQ_ASSIGN", "RIGHT_ASSIGN", "LBB",
  "FOR", "IN", "IF", "ELSE", "WHILE", "NEXT", "BREAK", "REPEAT", "GT",
  "GE", "LT", "LE", "EQ", "NE", "AND", "OR", "AND2", "OR2", "NS_GET",
  "NS_GET_INT", "COMMENT", "LINE_DIRECTIVE", "SYMBOL_FORMALS",
  "EQ_FORMALS", "EQ_SUB", "SYMBOL_SUB", "SYMBOL_FUNCTION_CALL",
  "SYMBOL_PACKAGE", "COLON_ASSIGN", "SLOT", "MINUS", "PLUS", "TILDE",
  "QUESTION", "COLON", "ASTERISK", "SLASH", "CARET", "SPECIAL", "LSQPAREN",
  "DOLLAR", "AT", "LOW", "'~'", "UNOT", "NOT", "UMINUS", "UPLUS",
  "$accept", "prog", "expr_or_assign_or_help", "expr_or_help", "expr",
  "cond", "ifcond", "forcond", "exprlist", "sublist", "sub", "formlist",
  "proglist", "formlist_inner", "cr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   143,   143,   145,   146,   150,   154,   157,   161,   165,
     166,   167,   170,   171,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   190,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   225,   230,   235,   242,   247,   252,   256,   261,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   282,   291,   300,   312,   313,   318,   324,
     330,   336,   344,   349,   357,   358,   359,   360,   361,   362,
     363,   364,   367,   368,   371,   377,   383,   390,   399
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    71,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    72,    73,    74,    75
    };
    const int user_token_number_max_ = 329;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= user_token_number_max_)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 9 "Parser.yxx"
} } } // rastr::r::parser
#line 2059 "Parser.cxx"

#line 402 "Parser.yxx"


void rastr::r::parser::Parser::error(const location_type& location, const std::string& message) {
    std::cerr << message << " at " << location;
}
