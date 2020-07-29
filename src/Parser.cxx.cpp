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
#line 101 "Parser.yxx"

    #include <string>
    #include <iostream>
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
  Parser::Parser (rastr::r::parser::Lexer& lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
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
#line 136 "Parser.yxx"
                                                                                { yyresult = 0; /*$1;*/ YYACCEPT; }
#line 639 "Parser.cxx"
    break;

  case 3:
#line 137 "Parser.yxx"
                                                                                { yyresult = 0; goto yyreturn; }
#line 645 "Parser.cxx"
    break;

  case 4:
#line 138 "Parser.yxx"
                                                                                { yyresult = 0; /*std::cout << $1 + $2;*/ goto yyreturn; }
#line 651 "Parser.cxx"
    break;

  case 5:
#line 139 "Parser.yxx"
                                                                                { yyresult = 0; /*std::cout << $1 + $2;*/ goto yyreturn; }
#line 657 "Parser.cxx"
    break;

  case 6:
#line 140 "Parser.yxx"
                                                                                { YYABORT; }
#line 663 "Parser.cxx"
    break;

  case 7:
#line 143 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 669 "Parser.cxx"
    break;

  case 8:
#line 144 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 675 "Parser.cxx"
    break;

  case 9:
#line 145 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 681 "Parser.cxx"
    break;

  case 10:
#line 148 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 687 "Parser.cxx"
    break;

  case 11:
#line 149 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 693 "Parser.cxx"
    break;

  case 12:
#line 152 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 699 "Parser.cxx"
    break;

  case 13:
#line 153 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 705 "Parser.cxx"
    break;

  case 14:
#line 154 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 711 "Parser.cxx"
    break;

  case 15:
#line 155 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 717 "Parser.cxx"
    break;

  case 16:
#line 156 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 723 "Parser.cxx"
    break;

  case 17:
#line 157 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 729 "Parser.cxx"
    break;

  case 18:
#line 158 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 735 "Parser.cxx"
    break;

  case 19:
#line 159 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 741 "Parser.cxx"
    break;

  case 20:
#line 160 "Parser.yxx"
                                                                                {
                                                                                  auto block = dynamic_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> set_delimiters(opening_delimiter, closing_delimiter);
                                                                                  yylhs.value = block;
                                                                                  lexer.disable_eat_lines();
                                                                                }
#line 754 "Parser.cxx"
    break;

  case 21:
#line 168 "Parser.yxx"
                                                                                { yylhs.value = new GroupExpressionRNode(wrap<DelimiterRNode>(yystack_[2].value),
                                                                                                                wrap<ExpressionRNode>(yystack_[1].value),
                                                                                                                wrap<DelimiterRNode>(yystack_[0].value)); }
#line 762 "Parser.cxx"
    break;

  case 22:
#line 171 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 768 "Parser.cxx"
    break;

  case 23:
#line 172 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 774 "Parser.cxx"
    break;

  case 24:
#line 173 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 780 "Parser.cxx"
    break;

  case 25:
#line 174 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 786 "Parser.cxx"
    break;

  case 26:
#line 175 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 792 "Parser.cxx"
    break;

  case 27:
#line 176 "Parser.yxx"
                                                                                { yylhs.value = create_unary_expression(yystack_[1].value, yystack_[0].value); }
#line 798 "Parser.cxx"
    break;

  case 28:
#line 177 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 804 "Parser.cxx"
    break;

  case 29:
#line 178 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 810 "Parser.cxx"
    break;

  case 30:
#line 179 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 816 "Parser.cxx"
    break;

  case 31:
#line 180 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 822 "Parser.cxx"
    break;

  case 32:
#line 181 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 828 "Parser.cxx"
    break;

  case 33:
#line 182 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 834 "Parser.cxx"
    break;

  case 34:
#line 183 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 840 "Parser.cxx"
    break;

  case 35:
#line 184 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 846 "Parser.cxx"
    break;

  case 36:
#line 185 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 852 "Parser.cxx"
    break;

  case 37:
#line 186 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 858 "Parser.cxx"
    break;

  case 38:
#line 187 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 864 "Parser.cxx"
    break;

  case 39:
#line 188 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 870 "Parser.cxx"
    break;

  case 40:
#line 189 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 876 "Parser.cxx"
    break;

  case 41:
#line 190 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 882 "Parser.cxx"
    break;

  case 42:
#line 191 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 888 "Parser.cxx"
    break;

  case 43:
#line 192 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 894 "Parser.cxx"
    break;

  case 44:
#line 193 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 900 "Parser.cxx"
    break;

  case 45:
#line 194 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 906 "Parser.cxx"
    break;

  case 46:
#line 195 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 912 "Parser.cxx"
    break;

  case 47:
#line 196 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 918 "Parser.cxx"
    break;

  case 48:
#line 197 "Parser.yxx"
                                                                                {
                                                                                  auto keyword = wrap<KeywordRNode>(yystack_[5].value);
                                                                                  auto params = delimit_expression_sequence(yystack_[3].value, yystack_[4].value, yystack_[2].value);
                                                                                  auto body = wrap<ExpressionRNode>(yystack_[0].value);
                                                                                  yylhs.value = new FunctionDefinitionExpressionRNode(keyword, params, body);
                                                                                }
#line 929 "Parser.cxx"
    break;

  case 49:
#line 203 "Parser.yxx"
                                                                                {
                                                                                  auto target = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto args = delimit_expression_sequence(yystack_[1].value, yystack_[2].value, yystack_[0].value);
                                                                                  yylhs.value = new FunctionCallExpressionRNode(target, args);
                                                                                }
#line 939 "Parser.cxx"
    break;

  case 50:
#line 208 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                        wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                        wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 949 "Parser.cxx"
    break;

  case 51:
#line 213 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new IfElseConditionalExpressionRNode(wrap<KeywordRNode>(yystack_[4].value),
                                                                                                                            wrap<ConditionRNode>(yystack_[3].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[2].value),
                                                                                                                            wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                            wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 961 "Parser.cxx"
    break;

  case 52:
#line 220 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new ForLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                  wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                  wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 971 "Parser.cxx"
    break;

  case 53:
#line 225 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new WhileLoopExpressionRNode(wrap<KeywordRNode>(yystack_[2].value),
                                                                                                                    wrap<ConditionRNode>(yystack_[1].value),
                                                                                                                    wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 981 "Parser.cxx"
    break;

  case 54:
#line 230 "Parser.yxx"
                                                                                {
                                                                                  yylhs.value = new RepeatLoopExpressionRNode(wrap<KeywordRNode>(yystack_[1].value),
                                                                                                                     wrap<ExpressionRNode>(yystack_[0].value));
                                                                                }
#line 990 "Parser.cxx"
    break;

  case 55:
#line 234 "Parser.yxx"
                                                                                {
                                                                                  auto expr = wrap<ExpressionRNode>(yystack_[4].value);
                                                                                  auto indices = delimit_expression_sequence(yystack_[2].value, yystack_[3].value, yystack_[1].value);
                                                                                  yylhs.value = new IndexingExpressionRNode(expr, indices);
                                                                                }
#line 1000 "Parser.cxx"
    break;

  case 56:
#line 239 "Parser.yxx"
                                                                                {
                                                                                  auto expr = wrap<ExpressionRNode>(yystack_[3].value);
                                                                                  auto indices = delimit_expression_sequence(yystack_[1].value, yystack_[2].value, yystack_[0].value);
                                                                                  yylhs.value = new IndexingExpressionRNode(expr, indices);
                                                                                }
#line 1010 "Parser.cxx"
    break;

  case 57:
#line 244 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1016 "Parser.cxx"
    break;

  case 58:
#line 245 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1022 "Parser.cxx"
    break;

  case 59:
#line 246 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1028 "Parser.cxx"
    break;

  case 60:
#line 247 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1034 "Parser.cxx"
    break;

  case 61:
#line 248 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1040 "Parser.cxx"
    break;

  case 62:
#line 249 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1046 "Parser.cxx"
    break;

  case 63:
#line 250 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1052 "Parser.cxx"
    break;

  case 64:
#line 251 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1058 "Parser.cxx"
    break;

  case 65:
#line 252 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1064 "Parser.cxx"
    break;

  case 66:
#line 253 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1070 "Parser.cxx"
    break;

  case 67:
#line 254 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1076 "Parser.cxx"
    break;

  case 68:
#line 255 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1082 "Parser.cxx"
    break;

  case 69:
#line 256 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value;  }
#line 1088 "Parser.cxx"
    break;

  case 70:
#line 257 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1094 "Parser.cxx"
    break;

  case 71:
#line 260 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1106 "Parser.cxx"
    break;

  case 72:
#line 269 "Parser.yxx"
                                                                                {
                                                                                  auto opening_delimiter = wrap<DelimiterRNode>(yystack_[2].value);
                                                                                  auto closing_delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  auto expr = wrap<RNode>(yystack_[1].value);
                                                                                  yylhs.value = new ConditionRNode(opening_delimiter, expr, closing_delimiter);
                                                                                  lexer.enable_eat_lines();
                                                                                }
#line 1118 "Parser.cxx"
    break;

  case 73:
#line 278 "Parser.yxx"
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
#line 1133 "Parser.cxx"
    break;

  case 74:
#line 290 "Parser.yxx"
                                                                                { yylhs.value = new BlockExpressionRNode(); }
#line 1139 "Parser.cxx"
    break;

  case 75:
#line 291 "Parser.yxx"
                                                                                {
                                                                                  auto block = new BlockExpressionRNode();
                                                                                  block -> append_expression(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1149 "Parser.cxx"
    break;

  case 76:
#line 296 "Parser.yxx"
                                                                                {
                                                                                  auto block = dynamic_cast<BlockExpressionRNode*>(yystack_[2].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  block -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1160 "Parser.cxx"
    break;

  case 77:
#line 302 "Parser.yxx"
                                                                                {
                                                                                  auto block = dynamic_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> append_delimiter(delimiter);
                                                                                  yylhs.value = block;
                                                                                }
#line 1171 "Parser.cxx"
    break;

  case 78:
#line 308 "Parser.yxx"
                                                                                {
                                                                                  auto block = dynamic_cast<BlockExpressionRNode*>(yystack_[2].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  block -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = block;
                                                                                }
#line 1182 "Parser.cxx"
    break;

  case 79:
#line 314 "Parser.yxx"
                                                                                {
                                                                                  auto block = dynamic_cast<BlockExpressionRNode*>(yystack_[1].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[0].value);
                                                                                  block -> append_delimiter(delimiter);
                                                                                  yylhs.value = block;
                                                                                }
#line 1193 "Parser.cxx"
    break;

  case 80:
#line 322 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  seq -> append_expression(wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1203 "Parser.cxx"
    break;

  case 81:
#line 327 "Parser.yxx"
                                                                                {
                                                                                  auto seq = dynamic_cast<ExpressionSequenceRNode*>(yystack_[3].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  seq -> append(delimiter, wrap<ExpressionRNode>(yystack_[0].value));
                                                                                  yylhs.value = seq;
                                                                                }
#line 1214 "Parser.cxx"
    break;

  case 82:
#line 335 "Parser.yxx"
                                                                                { yylhs.value = new MissingExpressionRNode(); }
#line 1220 "Parser.cxx"
    break;

  case 83:
#line 336 "Parser.yxx"
                                                                                { yylhs.value = yystack_[0].value; }
#line 1226 "Parser.cxx"
    break;

  case 84:
#line 337 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1232 "Parser.cxx"
    break;

  case 85:
#line 338 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1238 "Parser.cxx"
    break;

  case 86:
#line 339 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1244 "Parser.cxx"
    break;

  case 87:
#line 340 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1250 "Parser.cxx"
    break;

  case 88:
#line 341 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[0].value, yystack_[1].value, new MissingExpressionRNode()); }
#line 1256 "Parser.cxx"
    break;

  case 89:
#line 342 "Parser.yxx"
                                                                                { yylhs.value = create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value); }
#line 1262 "Parser.cxx"
    break;

  case 90:
#line 345 "Parser.yxx"
                                                                                { yylhs.value = new ExpressionSequenceRNode(); }
#line 1268 "Parser.cxx"
    break;

  case 91:
#line 346 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  seq -> append_expression(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1279 "Parser.cxx"
    break;

  case 92:
#line 352 "Parser.yxx"
                                                                                {
                                                                                  auto seq = new ExpressionSequenceRNode();
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  seq -> append_expression(element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1290 "Parser.cxx"
    break;

  case 93:
#line 358 "Parser.yxx"
                                                                                {
                                                                                  auto seq = dynamic_cast<ExpressionSequenceRNode*>(yystack_[2].value);
                                                                                  auto element = wrap<SymbolExpressionRNode>(yystack_[0].value);
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[1].value);
                                                                                  seq -> append(delimiter, element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1302 "Parser.cxx"
    break;

  case 94:
#line 365 "Parser.yxx"
                                                                                {
                                                                                  auto seq = dynamic_cast<ExpressionSequenceRNode*>(yystack_[4].value);
                                                                                  auto element = wrap<ExpressionRNode>(create_binary_expression(yystack_[1].value, yystack_[2].value, yystack_[0].value));
                                                                                  auto delimiter = wrap<DelimiterRNode>(yystack_[3].value);
                                                                                  seq -> append(delimiter, element);
                                                                                  yylhs.value = seq;
                                                                                }
#line 1314 "Parser.cxx"
    break;

  case 95:
#line 374 "Parser.yxx"
    { lexer.enable_eat_lines(); }
#line 1320 "Parser.cxx"
    break;


#line 1324 "Parser.cxx"

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


  const signed char Parser::yypact_ninf_ = -56;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     407,   -56,   429,   429,   429,   -56,   429,   -56,    -1,   -56,
     -56,   -56,   -56,   -56,   -56,    72,     9,    15,    19,    21,
     -56,   -56,   429,   429,   429,   429,   429,    26,   100,   108,
      25,   -21,    36,   322,   322,    -9,    -8,    -7,    12,    17,
      27,   429,   429,   429,   429,   429,    78,   135,   135,   235,
      78,   -56,   -56,   -56,   429,   429,   477,   429,   429,   477,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   477,    81,
      86,   -56,   -56,   429,   429,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,    84,    33,    68,    78,    24,   108,   -16,
      31,    78,    78,    78,   -17,    87,   -15,    53,   113,   -56,
     108,   191,   116,   337,   337,   337,   337,   337,   337,   322,
     279,   322,   279,    14,    14,   235,   135,    22,    22,   135,
     127,   117,   -56,   -56,   -56,   -56,   -21,   -21,   429,   -56,
     101,   429,   -56,   429,   429,   -56,   429,   429,   429,   -56,
     114,   124,   -56,    53,   429,   105,    32,   -56,    78,    53,
      53,    53,   477,   -56,    78,   429,   -56,   -56,    53
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     6,     0,    74,     0,     3,     0,     2,    16,    15,
      12,    13,    14,    17,    18,    19,     0,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,     0,     7,
       0,    75,     0,    24,    25,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,    54,    22,    23,    26,
      27,     1,     4,     5,     0,     0,    82,     0,     0,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    82,     0,
       0,    21,    20,    79,    77,    60,    59,    64,    63,    58,
      57,    62,    61,    91,     0,     0,    52,     0,    10,    50,
       0,    53,     8,     9,    16,    18,    19,    83,    95,    80,
      46,    47,    95,    41,    40,    36,    37,    38,    39,    42,
      43,    44,    45,    30,    29,    35,    28,    31,    32,    33,
      34,    95,    66,    65,    68,    67,    78,    76,     0,    95,
       0,     0,    72,     0,     0,    71,    86,    88,    84,    49,
       0,     0,    56,    92,     0,    93,     0,    11,    51,    87,
      89,    85,    82,    55,    48,     0,    73,    81,    94
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -56,   -56,    73,   -41,    -4,   -56,   -56,   -56,   -56,   -55,
     -30,   -56,     1
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,    27,    28,   107,    29,    45,    43,    41,    32,   108,
     109,    94,   150
  };

  const short
  Parser::yytable_[] =
  {
      33,    97,    34,   100,   112,    54,    85,    87,    89,   146,
      54,   148,    39,    86,    88,    90,   144,    56,    40,    47,
      48,    49,    42,   131,    44,    56,    51,    91,   142,    81,
      35,    36,    37,    38,    92,   145,   166,   139,    98,    93,
      98,    55,    59,    82,   140,    83,    35,    36,    84,    95,
      59,    54,    98,   110,   111,    98,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    98,    30,    31,    73,    74,    75,
      76,    77,    78,    79,    80,    73,   143,    55,    76,    77,
      78,    79,    80,   143,   143,    46,   132,   153,   141,    50,
     156,   134,   157,   133,    54,   159,   160,   161,   135,    52,
     138,    56,    53,   147,    96,   143,    99,   149,   101,    37,
      38,   151,   152,   155,   168,   162,    54,   102,   103,   163,
      56,   165,   167,    57,    98,    58,    59,    98,    56,    98,
     154,     0,    98,    98,    98,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    59,   136,   137,    98,     0,
       0,    98,    55,    59,     0,     0,     0,    70,    71,    72,
       0,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,    76,    56,    78,    79,    80,     0,     0,
       0,    76,     0,    78,    79,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   164,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    71,    72,     0,    73,    74,    75,    76,    77,    78,
      79,    80,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,     0,     0,    73,    74,
      75,    76,    77,    78,    79,    80,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,    60,    61,    62,    63,
      64,    65,    66,     0,    68,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      56,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      59,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    62,    63,    64,    65,    59,     0,     0,     0,     0,
       0,     0,     0,     0,    -1,    -1,    -1,    -1,    -1,    -1,
       0,    70,    71,     0,     0,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,     0,    70,    71,     0,     0,
      73,    74,    75,    76,    77,    78,    79,    80,     1,     0,
       2,     0,     0,     3,     0,     4,     5,     6,     0,     0,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     0,     2,     0,     0,     3,    17,     4,    18,     6,
      19,    20,    21,    22,     8,     9,    10,    11,    12,    13,
      14,    15,    16,     0,     0,     0,     0,     0,    17,     0,
      18,     0,    19,    20,    21,    22,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     0,     3,     0,     4,     0,     6,    23,    24,
      25,    26,   104,     9,    10,    11,    12,    13,   105,   106,
      16,     0,     0,     0,     0,     0,    17,     0,    18,     0,
      19,    20,    21,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    24,    25,    26
  };

  const short
  Parser::yycheck_[] =
  {
       4,    42,     6,    44,    59,    26,    15,    15,    15,    26,
      26,    26,     3,    22,    22,    22,    32,     3,     3,    23,
      24,    25,     3,    78,     3,     3,     0,    15,     4,     4,
      47,    48,    47,    48,    22,     4,     4,     4,    42,    22,
      44,    62,    28,     7,    11,     9,    47,    48,    12,    22,
      28,    26,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     2,     3,    63,    64,    65,
      66,    67,    68,    69,    70,    63,    62,    62,    66,    67,
      68,    69,    70,    62,    62,    22,    15,   138,    30,    26,
     141,    15,   143,    22,    26,   146,   147,   148,    22,     9,
      26,     3,    12,    26,    41,    62,    43,     4,    45,    47,
      48,     5,     5,    22,   165,    11,    26,    54,    55,     5,
       3,    26,   162,    25,   138,    27,    28,   141,     3,   143,
     139,    -1,   146,   147,   148,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    28,    83,    84,   162,    -1,
      -1,   165,    62,    28,    -1,    -1,    -1,    59,    60,    61,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    66,     3,    68,    69,    70,    -1,    -1,
      -1,    66,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   144,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   154,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
       3,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      -1,    59,    60,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    59,    60,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,     1,    -1,
       3,    -1,    -1,     6,    -1,     8,     9,    10,    -1,    -1,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,     3,    -1,    -1,     6,    29,     8,    31,    10,
      33,    34,    35,    36,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    33,    34,    35,    36,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,     6,    -1,     8,    -1,    10,    59,    60,
      61,    62,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     1,     3,     6,     8,     9,    10,    13,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    29,    31,    33,
      34,    35,    36,    59,    60,    61,    62,    78,    79,    81,
      79,    79,    85,    81,    81,    47,    48,    47,    48,     3,
       3,    84,     3,    83,     3,    82,    79,    81,    81,    81,
      79,     0,     9,    12,    26,    62,     3,    25,    27,    28,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    69,
      70,     4,     7,     9,    12,    15,    22,    15,    22,    15,
      22,    15,    22,    22,    88,    22,    79,    80,    81,    79,
      80,    79,    79,    79,    15,    21,    22,    80,    86,    87,
      81,    81,    86,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    86,    15,    22,    15,    22,    79,    79,    26,     4,
      11,    30,     4,    62,    32,     4,    26,    26,    26,     4,
      89,     5,     5,    80,    89,    22,    80,    80,    79,    80,
      80,    80,    11,     5,    79,    26,     4,    87,    80
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    77,    78,    78,    78,    78,    78,    79,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    83,    84,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    88,    88,    88,    89
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     1,     1,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     2,     2,     2,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     4,
       3,     5,     3,     3,     2,     5,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     3,     5,     0,     1,     3,     2,     3,     2,
       1,     4,     0,     1,     2,     3,     2,     3,     2,     3,
       0,     1,     3,     3,     5,     0
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "LPAREN", "RPAREN",
  "RSQPAREN", "LBRACE", "RBRACE", "EXCLAMATION", "NEWLINE",
  "DOUBLE_EXCLAMATION", "COMMA", "SEMICOLON", "END_OF_INPUT", "ERROR",
  "STR_CONST", "LITERAL_CONST", "INT_CONST", "FLOAT_CONST",
  "COMPLEX_CONST", "RAW_STRING_CONST", "NULL_CONST", "SYMBOL", "FUNCTION",
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
  "cr", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   136,   136,   137,   138,   139,   140,   143,   144,   145,
     148,   149,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   168,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   203,
     208,   213,   220,   225,   230,   234,   239,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   260,   269,   278,   290,   291,   296,   302,   308,   314,
     322,   327,   335,   336,   337,   338,   339,   340,   341,   342,
     345,   346,   352,   358,   365,   374
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
       2,     2,     2,     2,     2,     2,    72,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    73,    74,    75,
      76
    };
    const int user_token_number_max_ = 330;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= user_token_number_max_)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 9 "Parser.yxx"
} } } // rastr::r::parser
#line 2031 "Parser.cxx"

#line 377 "Parser.yxx"


void rastr::r::parser::Parser::error(const location_type& location, const std::string& message) {
    std::cerr << message << " at " << location;
}
