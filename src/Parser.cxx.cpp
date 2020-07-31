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
    return new BinaryOperationExpressionRNode(op, left_expr, right_expr);
}

RNode* create_unary_expression(RNode* op_ptr, RNode* expr_ptr) {
    auto op = wrap<OperatorRNode>(op_ptr);
    auto expr = wrap<ExpressionRNode>(expr_ptr);
    return new UnaryOperationExpressionRNode(op, expr);
}

void add_terminator(ExpressionSequenceRNode* seq_ptr, RNode* delimiter_ptr) {
    auto delimiter = wrap<DelimiterRNode>(delimiter_ptr);
    int size = seq_ptr -> get_size();
    if(size == 0) { return; }
    auto expr = seq_ptr -> get_element(size - 1);
    auto terminated_expr = std::make_shared<TerminatedExpressionRNode>(expr, delimiter);
    seq_ptr -> set_element(size - 1, terminated_expr);
}


#line 79 "Parser.cxx"


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
#line 172 "Parser.cxx"

  /// Build a parser object.
  Parser::Parser (rastr::r::parser::Lexer& lexer_yyarg, rastr::ast::ProgramRNodeSPtr& program_yyarg)
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
#line 142 "Parser.yxx"
                                                                                {
                                                                                  auto begin = std::make_shared<BeginRNode>();
                                                                                  auto exprs = wrap<ExpressionSequenceRNode>(yystack_[1].value);
                                                                                  auto end = wrap<EndRNode>(yystack_[0].value);
                                                                                  program.reset(new ProgramRNode(begin, exprs, end));
                                                                                  yyresult = 0;
                                                                                  YYACCEPT;
                                                                                }
#line 647 "Parser.cxx"
    break;

  case 3:
#line 151 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 653 "Parser.cxx"
    break;

  case 4:
#line 152 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 659 "Parser.cxx"
    break;

  case 5:
#line 153 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 665 "Parser.cxx"
    break;

  case 6:
#line 156 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 671 "Parser.cxx"
    break;

  case 7:
#line 157 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 677 "Parser.cxx"
    break;

  case 8:
#line 160 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 683 "Parser.cxx"
    break;

  case 9:
#line 161 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 689 "Parser.cxx"
    break;

  case 10:
#line 162 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 695 "Parser.cxx"
    break;

  case 11:
#line 163 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 701 "Parser.cxx"
    break;

  case 12:
#line 164 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 707 "Parser.cxx"
    break;

  case 13:
#line 165 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 713 "Parser.cxx"
    break;

  case 14:
#line 166 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 719 "Parser.cxx"
    break;

  case 15:
#line 167 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 725 "Parser.cxx"
    break;

  case 16:
#line 168 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto exprs = wrap<ExpressionSequenceRNode>(yystack_[1].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  yylhs.value = new BlockExpressionRNode(opening_delimiter, exprs, closing_delimiter);
                                                                                  lexer.disable_eat_lines();
                                                                                }
#line 737 "Parser.cxx"
    break;

  case 17:
#line 175 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto body = wrap<ExpressionRNode>(yystack_[1].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  yylhs.value = new GroupExpressionRNode(opening_delimiter, body, closing_delimiter);
                                                                                }
#line 748 "Parser.cxx"
    break;

  case 18:
#line 181 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 754 "Parser.cxx"
    break;

  case 19:
#line 182 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 760 "Parser.cxx"
    break;

  case 20:
#line 183 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 766 "Parser.cxx"
    break;

  case 21:
#line 184 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 772 "Parser.cxx"
    break;

  case 22:
#line 185 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 778 "Parser.cxx"
    break;

  case 23:
#line 186 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 784 "Parser.cxx"
    break;

  case 24:
#line 187 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 790 "Parser.cxx"
    break;

  case 25:
#line 188 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 796 "Parser.cxx"
    break;

  case 26:
#line 189 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 802 "Parser.cxx"
    break;

  case 27:
#line 190 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 808 "Parser.cxx"
    break;

  case 28:
#line 191 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 814 "Parser.cxx"
    break;

  case 29:
#line 192 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 820 "Parser.cxx"
    break;

  case 30:
#line 193 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 826 "Parser.cxx"
    break;

  case 31:
#line 194 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 832 "Parser.cxx"
    break;

  case 32:
#line 195 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 838 "Parser.cxx"
    break;

  case 33:
#line 196 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 844 "Parser.cxx"
    break;

  case 34:
#line 197 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 850 "Parser.cxx"
    break;

  case 35:
#line 198 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 856 "Parser.cxx"
    break;

  case 36:
#line 199 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 862 "Parser.cxx"
    break;

  case 37:
#line 200 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 868 "Parser.cxx"
    break;

  case 38:
#line 201 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 874 "Parser.cxx"
    break;

  case 39:
#line 202 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 880 "Parser.cxx"
    break;

  case 40:
#line 203 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 886 "Parser.cxx"
    break;

  case 41:
#line 204 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 892 "Parser.cxx"
    break;

  case 42:
#line 205 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 898 "Parser.cxx"
    break;

  case 43:
#line 206 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 904 "Parser.cxx"
    break;

  case 44:
#line 207 "Parser.yxx"
                                                                                {
                                                                                  auto keyword = wrap<KeywordRNode>(yystack_[5].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[4].value);
                                                                                  auto params = wrap<ExpressionSequenceRNode>(yystack_[3].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto body = wrap<ExpressionRNode>(yystack_[0].value);
                                                                                  yylhs.value = new FunctionDefinitionExpressionRNode(keyword, opening_delimiter, params, closing_delimiter, body);
                                                                                }
#line 917 "Parser.cxx"
    break;

  case 45:
#line 215 "Parser.yxx"
                                                                                {
                                                                                  auto target = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto args = wrap<ExpressionSequenceRNode>(yystack_[1].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  yylhs.value = new FunctionCallExpressionRNode(target, opening_delimiter, args, closing_delimiter);
                                                                                }
#line 929 "Parser.cxx"
    break;

  case 46:
#line 222 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                        wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                        wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 939 "Parser.cxx"
    break;

  case 47:
#line 227 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfElseConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[4].value),
                                                                                                                            wrap<ConditionRNode>(yystack_[3].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[2].value),
                                                                                                                            wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 951 "Parser.cxx"
    break;

  case 48:
#line 234 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new ForLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                  wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                  wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 961 "Parser.cxx"
    break;

  case 49:
#line 239 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new WhileLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                    wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                    wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 971 "Parser.cxx"
    break;

  case 50:
#line 244 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new RepeatLoopExpressionRNode(wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                     wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 980 "Parser.cxx"
    break;

  case 51:
#line 248 "Parser.yxx"
                                                                                {
                                                                                  auto object = wrap<ExpressionRNode>(yystack_[4].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[3].value);
                                                                                  auto indices = wrap<ExpressionSequenceRNode>(yystack_[2].value);
                                                                                  auto first_closing_delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  auto second_closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  yylhs.value =  new IndexingExpressionRNode(object,
                                                                                                                    opening_delimiter,
                                                                                                                    indices,
                                                                                                                    first_closing_delimiter,
                                                                                                                    second_closing_delimiter);
                                                                                }
#line 997 "Parser.cxx"
    break;

  case 52:
#line 260 "Parser.yxx"
                                                                                {
                                                                                  auto object = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto indices = wrap<ExpressionSequenceRNode>(yystack_[1].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  yylhs.value =  new SubsettingExpressionRNode(object,
                                                                                                                      opening_delimiter,
                                                                                                                      indices,
                                                                                                                      closing_delimiter);
                                                                                }
#line 1012 "Parser.cxx"
    break;

  case 53:
#line 270 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1018 "Parser.cxx"
    break;

  case 54:
#line 271 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1024 "Parser.cxx"
    break;

  case 55:
#line 272 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1030 "Parser.cxx"
    break;

  case 56:
#line 273 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1036 "Parser.cxx"
    break;

  case 57:
#line 274 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1042 "Parser.cxx"
    break;

  case 58:
#line 275 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1048 "Parser.cxx"
    break;

  case 59:
#line 276 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1054 "Parser.cxx"
    break;

  case 60:
#line 277 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1060 "Parser.cxx"
    break;

  case 61:
#line 278 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1066 "Parser.cxx"
    break;

  case 62:
#line 279 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1072 "Parser.cxx"
    break;

  case 63:
#line 280 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1078 "Parser.cxx"
    break;

  case 64:
#line 281 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1084 "Parser.cxx"
    break;

  case 65:
#line 282 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1090 "Parser.cxx"
    break;

  case 66:
#line 283 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1096 "Parser.cxx"
    break;

  case 67:
#line 286 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1108 "Parser.cxx"
    break;

  case 68:
#line 295 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1120 "Parser.cxx"
    break;

  case 69:
#line 304 "Parser.yxx"
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
#line 1135 "Parser.cxx"
    break;

  case 70:
#line 316 "Parser.yxx"
                                                                                { yylhs.value = new ExpressionSequenceRNode(); }
#line 1141 "Parser.cxx"
    break;

  case 71:
#line 317 "Parser.yxx"
                                                                                {
                                                                                  auto block = new ExpressionSequenceRNode();
                                                                                  block -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1151 "Parser.cxx"
    break;

  case 72:
#line 322 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<ExpressionSequenceRNode*>(yystack_[2].value);
                                                                                  add_terminator(block, yystack_[1].value);
                                                                                  block -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1162 "Parser.cxx"
    break;

  case 73:
#line 328 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<ExpressionSequenceRNode*>(yystack_[1].value);
                                                                                  add_terminator(block, yystack_[0].value);
                                                                                  yylhs.value = block;
                                                                                }
#line 1172 "Parser.cxx"
    break;

  case 74:
#line 333 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<ExpressionSequenceRNode*>(yystack_[2].value);
                                                                                  add_terminator(block, yystack_[1].value);
                                                                                  block -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1183 "Parser.cxx"
    break;

  case 75:
#line 339 "Parser.yxx"
                                                                                {
                                                                                  auto block = static_cast<ExpressionSequenceRNode*>(yystack_[1].value);
                                                                                  add_terminator(block, yystack_[0].value);
                                                                                  yylhs.value = block;
                                                                                }
#line 1193 "Parser.cxx"
    break;

  case 76:
#line 346 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  seq -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1203 "Parser.cxx"
    break;

  case 77:
#line 351 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[3].value);
                                                                                  add_terminator(seq, yystack_[1].value);
                                                                                  seq -> push_back(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1214 "Parser.cxx"
    break;

  case 78:
#line 359 "Parser.yxx"
                                                                                { yylhs.value = new MissingExpressionRNode(); }
#line 1220 "Parser.cxx"
    break;

  case 79:
#line 360 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1226 "Parser.cxx"
    break;

  case 80:
#line 361 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1232 "Parser.cxx"
    break;

  case 81:
#line 362 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1238 "Parser.cxx"
    break;

  case 82:
#line 363 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1244 "Parser.cxx"
    break;

  case 83:
#line 364 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1250 "Parser.cxx"
    break;

  case 84:
#line 365 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1256 "Parser.cxx"
    break;

  case 85:
#line 366 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1262 "Parser.cxx"
    break;

  case 86:
#line 369 "Parser.yxx"
                                                                                { yylhs.value = new ExpressionSequenceRNode(); }
#line 1268 "Parser.cxx"
    break;

  case 87:
#line 370 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1274 "Parser.cxx"
    break;

  case 88:
#line 373 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  seq -> push_back(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1285 "Parser.cxx"
    break;

  case 89:
#line 379 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  seq -> push_back(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1296 "Parser.cxx"
    break;

  case 90:
#line 385 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[2].value);
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  add_terminator(seq, yystack_[1].value);
                                                                                  seq -> push_back(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1308 "Parser.cxx"
    break;

  case 91:
#line 392 "Parser.yxx"
                                                                                {
                                                                                  auto seq = static_cast<ExpressionSequenceRNode*>(yystack_[4].value);
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  add_terminator(seq, yystack_[3].value);
                                                                                  seq -> push_back(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1320 "Parser.cxx"
    break;

  case 92:
#line 401 "Parser.yxx"
    { lexer.enable_eat_lines(); }
#line 1326 "Parser.cxx"
    break;


#line 1330 "Parser.cxx"

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


  const signed char Parser::yypact_ninf_ = -51;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     402,   402,   402,   402,   402,    -4,   -51,   -51,   -51,   -51,
     -51,   -51,    49,     3,     8,    13,    19,   -51,   -51,   402,
     402,   402,   402,   402,    44,   -22,   124,    91,    21,    23,
     320,   320,   -12,    -6,    26,    77,    76,    81,   402,   402,
     402,   402,   402,    82,   131,   131,   234,    82,   -51,   402,
     402,   436,   402,   402,   436,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   436,    78,    80,   402,   402,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,    88,
      30,   -51,    89,    82,    20,   124,   -11,    27,    82,    82,
      82,   -20,    92,   -18,    60,   101,   -51,   124,   191,   117,
     335,   335,   335,   335,   335,   335,   320,   277,   320,   277,
      10,    10,   234,   131,    18,    18,   131,   176,   118,   -51,
     -51,   -51,   -51,   -22,   -22,   402,   -51,   103,   402,   -51,
     402,   402,   -51,   402,   402,   402,   -51,   114,   121,   -51,
      60,   402,   104,    29,   -51,    82,    60,    60,    60,   436,
     -51,    82,   402,   -51,   -51,    60
  };

  const signed char
  Parser::yydefact_[] =
  {
      70,     0,    70,     0,     0,    12,    11,     8,     9,    10,
      13,    14,    15,     0,     0,     0,     0,    65,    66,     0,
       0,     0,     0,     0,     0,    71,     3,     0,     0,     0,
      20,    21,     0,     0,     0,     0,    86,     0,     0,     0,
       0,     0,     0,    50,    18,    19,    22,    23,     1,     0,
       0,    78,     0,     0,    78,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,    75,    73,     2,    17,
      16,    56,    55,    60,    59,    54,    53,    58,    57,    88,
       0,    87,     0,    48,     0,     6,    46,     0,    49,     4,
       5,    12,    14,    15,    79,    92,    76,    42,    43,    92,
      37,    36,    32,    33,    34,    35,    38,    39,    40,    41,
      26,    25,    31,    24,    27,    28,    29,    30,    92,    62,
      61,    64,    63,    74,    72,     0,    92,     0,     0,    68,
       0,     0,    67,    82,    84,    80,    45,     0,     0,    52,
      89,     0,    90,     0,     7,    47,    83,    85,    81,    78,
      51,    44,     0,    69,    77,    91
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -51,   -51,    70,   -29,    -3,   -51,   -51,   -51,   126,   -50,
     -28,   -51,   -51,     0
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,    24,    25,   104,    26,    42,    40,    38,    27,   105,
     106,    90,    91,   147
  };

  const short
  Parser::yytable_[] =
  {
      30,    31,    81,    49,   109,   143,    36,   145,    83,    82,
      94,    37,    97,    51,    49,    84,    39,    44,    45,    46,
     141,    51,    41,   128,   139,    79,    32,    33,    34,    35,
      80,   142,    76,   163,   136,    77,    95,    54,    95,    50,
      85,   137,    32,    33,    48,    54,    49,    86,    95,   107,
     108,    95,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      95,    28,    68,    69,    70,    71,    72,    73,    74,    75,
      68,   140,    50,    71,    72,    73,    74,    75,   140,    43,
     140,    87,   129,    47,   131,    34,    35,    89,    88,   130,
      76,   132,    92,    77,    78,   146,   150,    49,    93,   153,
      96,   154,    98,   135,   156,   157,   158,   144,   138,    99,
     100,   140,   148,   149,   152,   159,   160,    51,    29,   162,
       0,   164,    95,   165,    51,    95,   151,    95,     0,     0,
      95,    95,    95,     0,     0,     0,   133,   134,    52,     0,
      53,    54,     0,     0,     0,     0,    95,     0,    54,    95,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    65,    66,    67,     0,    68,    69,    70,    71,
      72,    73,    74,    75,    51,     0,    71,     0,    73,    74,
      75,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,   155,     0,     0,     0,     0,     0,     0,    54,     0,
       0,   161,     0,     0,     0,     0,     0,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    51,    68,     0,
       0,    71,     0,    73,    74,    75,     0,     0,     0,    65,
      66,    67,     0,    68,    69,    70,    71,    72,    73,    74,
      75,    54,     0,     0,     0,     0,     0,     0,     0,     0,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,     0,     0,    68,    69,    70,    71,
      72,    73,    74,    75,    54,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    56,    57,    58,    59,    60,    61,
       0,    63,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,     0,    51,    68,
      69,    70,    71,    72,    73,    74,    75,    54,     0,     0,
       0,     0,     0,     0,     0,     0,    55,    56,    57,    58,
      59,    60,    54,     0,     0,     0,     0,     0,     0,     0,
       0,    -1,    -1,    -1,    -1,    -1,    -1,     0,    65,    66,
       0,     0,    68,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,    65,    66,     0,     0,    68,    69,    70,
      71,    72,    73,    74,    75,     1,     0,     0,     2,     0,
       3,     0,     4,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
      14,     0,    15,     0,    16,    17,    18,    19,     0,     1,
       0,     0,     2,     0,     3,     0,     4,     0,     0,     0,
     101,     6,     7,     8,     9,    10,   102,   103,    13,     0,
      20,    21,    22,    23,    14,     0,    15,     0,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    21,    22,    23
  };

  const short
  Parser::yycheck_[] =
  {
       3,     4,    14,    25,    54,    25,     3,    25,    14,    21,
      39,     3,    41,     3,    25,    21,     3,    20,    21,    22,
      31,     3,     3,    73,     4,     4,    46,    47,    46,    47,
       7,     4,     9,     4,     4,    12,    39,    27,    41,    61,
      14,    11,    46,    47,     0,    27,    25,    21,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     1,    62,    63,    64,    65,    66,    67,    68,    69,
      62,    61,    61,    65,    66,    67,    68,    69,    61,    19,
      61,    14,    14,    23,    14,    46,    47,    21,    21,    21,
       9,    21,    21,    12,    13,     4,   135,    25,    38,   138,
      40,   140,    42,    25,   143,   144,   145,    25,    29,    49,
      50,    61,     5,     5,    21,    11,     5,     3,     2,    25,
      -1,   159,   135,   162,     3,   138,   136,   140,    -1,    -1,
     143,   144,   145,    -1,    -1,    -1,    76,    77,    24,    -1,
      26,    27,    -1,    -1,    -1,    -1,   159,    -1,    27,   162,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    58,    59,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,     3,    -1,    65,    -1,    67,    68,
      69,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,   151,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,     3,    62,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    -1,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    -1,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    -1,     3,    62,
      63,    64,    65,    66,    67,    68,    69,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    40,    41,    -1,    58,    59,
      -1,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    58,    59,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,     3,    -1,    -1,     6,    -1,
       8,    -1,    10,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    30,    -1,    32,    33,    34,    35,    -1,     3,
      -1,    -1,     6,    -1,     8,    -1,    10,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    -1,
      58,    59,    60,    61,    28,    -1,    30,    -1,    32,    33,
      34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     6,     8,    10,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    28,    30,    32,    33,    34,    35,
      58,    59,    60,    61,    77,    78,    80,    84,    78,    84,
      80,    80,    46,    47,    46,    47,     3,     3,    83,     3,
      82,     3,    81,    78,    80,    80,    80,    78,     0,    25,
      61,     3,    24,    26,    27,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    58,    59,    60,    62,    63,
      64,    65,    66,    67,    68,    69,     9,    12,    13,     4,
       7,    14,    21,    14,    21,    14,    21,    14,    21,    21,
      87,    88,    21,    78,    79,    80,    78,    79,    78,    78,
      78,    14,    20,    21,    79,    85,    86,    80,    80,    85,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    85,    14,
      21,    14,    21,    78,    78,    25,     4,    11,    29,     4,
      61,    31,     4,    25,    25,    25,     4,    89,     5,     5,
      79,    89,    21,    79,    79,    78,    79,    79,    79,    11,
       5,    78,    25,     4,    86,    79
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    76,    77,    78,    78,    78,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    81,    82,    83,
      84,    84,    84,    84,    84,    84,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    88,    88,
      88,    88,    89
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     6,     4,     3,     5,     3,     3,
       2,     5,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     3,     3,     5,
       0,     1,     3,     2,     3,     2,     1,     4,     0,     1,
       2,     3,     2,     3,     2,     3,     0,     1,     1,     3,
       3,     5,     0
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
  "formlist_inner", "cr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   142,   142,   151,   152,   153,   156,   157,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   175,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   215,   222,   227,   234,   239,
     244,   248,   260,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   286,   295,   304,
     316,   317,   322,   328,   333,   339,   346,   351,   359,   360,
     361,   362,   363,   364,   365,   366,   369,   370,   373,   379,
     385,   392,   401
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
#line 2028 "Parser.cxx"

#line 404 "Parser.yxx"


void rastr::r::parser::Parser::error(const location_type& location, const std::string& message) {
    std::cerr << message << " at " << location;
}
