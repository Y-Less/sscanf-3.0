#include "../parser.h"
#include "../specifiers.h"

TEST(PC0, { Specifier * spec; return gParser.Compile(S"", &spec) == ERROR_NO_CHILDREN; })
TEST(PC1, { Specifier * spec; return gParser.Compile(S"ii", &spec) == OK && spec->GetSpecifier() == '\0'; })
TEST(PC5, { Specifier * spec; return gParser.Compile(S"iiq", &spec) == ERROR_UNKNOWN_SPECIFIER; })
TEST(PC2, { Specifier * spec; return gParser.Compile(S"ii|dd", &spec) == OK && spec->GetSpecifier() == '('; })
TEST(PC3, { Specifier * spec; return gParser.Compile(S"i|X(0xFF)", &spec) == OK && spec->GetSpecifier() == '(' && spec->CountChildren() == 2; })

TEST(PC4a, { Specifier * spec; return gParser.Compile(S"iC('q')|(x|x)", &spec) == OK && spec->GetSpecifier() == '('; })
TEST(PC4c, { Specifier * spec; return gParser.Compile(S"iC('q')-|(x|-x-)", &spec) == OK && spec->GetSpecifier() == '('; })
TEST(PC4b, { Specifier * spec; gParser.Compile(S"i C ( 'q')   |(   x|x)", &spec); ss s; return
	dynamic_cast<ss &>(s << *spec).str() == "ic|(x|x)"; })



TEST(GN7,  { Specifier * s = nullptr; return gParser.GetNext(S"\xFF;", &s) == ERROR_UNKNOWN_SPECIFIER; })
TEST(GN8,  { Specifier * s = nullptr; return gParser.GetNext(S"		", &s) == OK; })
TEST(GN9,  { Specifier * s = nullptr; return gParser.GetNext(S"~", &s) == ERROR_UNKNOWN_SPECIFIER; })
TEST(GN10, { Specifier * s = nullptr; return gParser.GetNext(S"^", &s) == ERROR_UNKNOWN_SPECIFIER; })

TEST(GN0,  { Specifier * s = nullptr; return gParser.GetNext(S"i", &s) == OK && s && s->GetSpecifier() == 'i'; })
TEST(GN1,  { Specifier * s = nullptr; return gParser.GetNext(S"", &s) == OK && !s; })
TEST(GN2,  { Specifier * s = nullptr; return gParser.GetNext(S"d", &s) == OK && s && s->GetSpecifier() == 'd'; })
TEST(GN3,  { Specifier * s = nullptr; return gParser.GetNext(S"x", &s) == OK && s && s->GetSpecifier() == 'x'; })
TEST(GN4,  { Specifier * s = nullptr; return gParser.GetNext(S"'", &s) == ERROR_NO_STRING_END; })

TEST(GN5,  { Specifier * s = nullptr; char const * p = "oxc"; return
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'o' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'x' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'c' &&
	gParser.GetNext(p, &s) == OK && !s; })

TEST(GN6,  { Specifier * s = nullptr; char const * p = "   o   x   c   "; return
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'o' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'x' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'c' &&
	gParser.GetNext(p, &s) == OK && !s; })

TEST(GN11, { Specifier * s = nullptr; return gParser.GetNext(S"I(45)", &s) == OK && s && s->GetSpecifier() == 'i'; })

TEST(GN12, { Specifier * s = nullptr; char const * p = S"   B  (  0b001101  )   d  H(FF) "; return
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'b' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'd' &&
	gParser.GetNext(p, &s) == OK && s && s->GetSpecifier() == 'h' &&
	gParser.GetNext(p, &s) == OK && !s; })

TEST(Parser1, { Parser p; return '~' - '!' < sizeof (p.m_specifiers) / sizeof (Specifier *); })
