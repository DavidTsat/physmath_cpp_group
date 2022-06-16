#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include "csv_parse.h"

using namespace std;

/*
1. match "regular expression" "regular expressions", "regexes", "regex", "regexp"

reg(ular expressions?|ex(p|es)?) ////////////

regular expression
 regular expressions",
"regexes",
"regex",  dsfsd
regexpsdf sd
sdfsd

2. match 1+1=2
1\+1=2
.+\+.+=.+						////////////

1+1=2
1111=2
5+7=12
 9 + 4 = 13


Escaping a single metacharacter with a backslash works in all regular expression flavors. Many flavors also
support the \Q...\E escape sequence. All the characters between the \Q and the \E are interpreted as literal
characters. E.g. «\Q*\d+*\E» matches the literal text „*\d+*”

3. Match C:\temp
^[a-zA-Z]:\\temp

 Use «\t» to match a tab character (ASCII 0x09), «\r» for carriage return (0x0D) and «\n» for line feed (0x0A)

With a "character class", also called “character set”, you can tell the regex engine to match only one out of
several characters. Simply place the characters you want to match between square brackets. 

4. Find a word, even if it is misspelled, such as «sep[ae]r[ae]te» or «li[cs]en[cs]e».
5. Find an identifier in a programming language with «[A-Za-z_][A-Za-z_0-9]*».
6. Find a C-style hexadecimal number with «0[xX][A-Fa-f0-9]+»

Typing a caret after the opening square bracket will negate the character class. The result is that the character
class will match any character that is not in the character class - q[^u]
If you want the regex to match the q, and only the q, in both
strings, you need to use negative lookahead: «q(?!u)». But we will get to that later (?<=q)u

Note that the only special characters or metacharacters inside a character class are the closing bracket (]), the
backslash (\), the caret (^) and the hyphen (-). The usual metacharacters are normal characters inside a
character class, and do not need to be escaped by a backslash. To include a backslash as a character without any special meaning inside a character class, you have to escape
it with another backslash. «[\\x]» matches a backslash or an x
 The closing bracket (]), the caret (^) and the
hyphen (-) can be included by escaping them with a backslash, or by placing them in a position where they do
not take on their special meaning. I recommend the latter method, since it improves readability. To include a
caret, place it anywhere except right after the opening bracket. «[x^]» matches an x or a caret. You can put
the closing bracket right after the opening bracket, or the negating caret. «[]x]» matches a closing bracket or
an x. «[^]x]» matches any character that is not a closing bracket or an x
«[\Q[-]\E]» matches „[”, „-” or „]”
\s\d vs [\s\d]    - ex 1 + 2 = 3

«[\da-fA-F]» matches a hexadecimal digit

[^\d\s] vs [\D\S]

7. If you want to repeat the matched character, rather than the class, you will need to use backreferences. «([0-9])\1+» will match „222” but not “837”

8. Match date mm/dd/yyyy mm.dd.yyyy mm-dd-yyyy
(((0|1|2)[1-9])|((30)|(31)|(32)))([.\-\/])\d\d\8\d\d\d\d
250222251556
08.06.2022
03-06-2022
31-06-2022
32-06-2022
08/06/2022
08/06-2022
88/06/2022
18-86-2022
08.06.0195
08062022
08\06\2022

9. match a double-quoted string.
".*"    vs      "[^"\n\r]*"    vs  ".*?"  


Put a "string" between double quotes
“Houston, we have a problem with "string one" and "string two". Please respond.
dmskf d "skfdl"

Anchors ^ and $
^a , bc$
abc
bc
10. example (with anchors) match integer
\d+ vs ^\d+$

145
154.9
sdfa56
87sfa
trim whitespaces - (^\d+$)|((?<=\s)\d+$)
   78

Word Boundaries - \b \B
\bis\b
This island is beautiful

Alternation with The Vertical Bar or Pipe Symbol
11. \bcat|dog|mouse\b vs \b(cat|dog|mouse)\b
sdfmsd cat
scsccatsdf
sdfsdogsfsd
skms dog sfs cat

12. Get|GetValue|Set|SetValue
SetValue
Get(Value)?|Set(Value)? - greedy
(Get|Set)(Value)?? - lazy

SetValue
SetValueFunction

13. Feb 23(rd)? vs Feb 23(rd)??
Today is Feb 23rd, 2003

14. 
match a number between 1000 and 9999
\b[1-9][0-9]{3}\b

15. match a number [700, 6999]
\b(([1-6])|([789]))\d\d(?(2)\d|)\b or \b(([1-6])|([789]))\d{2}(?(2)\d|)\b
1000
1120
9998
9999
0112
99991
700
699
780
781
6999
7000
7818
952
1543
1544

16. HTML Tag <.+> vs <.*?> vs <[^>]+>
This is a <EM>first</EM> test

Use Round Brackets for Grouping and BackReference 
Non-capturing group (?:Value)
If you do not use the backreference, you can optimize this regular expression into «Set(?:Value)?»

17. HTML Tag with the same name
(?i)<([A-Z][A-Z0-9]*)[^>]*>.*?<\/\1>

18. ([abc]+) vs ([abc])+  vs ([abc])+\1
cab
cabb
cabc
cabcab

((\w)+)\1 vs ((\w)+)\2

18. Checking for Doubled Words like the the

\b(\w+)\s\1\b
I said him that the the ...

Regex Matching Modes: /i, /s, /m, /x

Possesive vs Greedy vs Lazy
19. "[^"]*+"
"abc"
"abc
The main practical benefit of possessive quantifiers is to speed up your regular expression. In particular,
possessive quantifiers allow your regex to fail faster
E.g. «".*"» will match „"abc"” in “"abc"x”, but «".*+"» will not match this string at all
20. ".*" vs ".*+"
"abc"
"abc
"abc"fsdfsdf

21. Atomic Group
An atomic group is a group that, when the regex engine exits from it, automatically throws away all
backtracking positions remembered by any tokens inside the group

22. (?>.*)c
bbabbbabbbbc

23. the (big|small|biggest) (cat|dog|bird) vs the (?>big|small|biggest) (cat|dog|bird)
the big dog
the small bird
the biggest dog
the small cat

24. \b(?>insert|in|integer)\b \b(?>in|integer|insert)\b
insert 

. Lookahead and Lookbehind Zero-Width Assertions
(?!) - negative lookahead
(?=) - positive lookahead
(?<=) - positive lookbehind
(?<!) - negative lookbehind

Positive lookahead works just the same. «q(?=u)» matches a q that is followed by a u, without making the u
part of the match
25. «q(?=u)i» to “quit”

Note that the lookahead itself does not create a
backreference. So it is not included in the count towards numbering the backreferences. If you want to store
the match of the regex inside a backreference, you have to put capturing parentheses around the regex inside
the lookahead, like this: «(?=(regex))»

Given the string foobarbarfoo
bar(?=bar)     finds the 1st bar ("bar" which has "bar" after it)
bar(?!bar)     finds the 2nd bar ("bar" which does not have "bar" after it)
(?<=foo)bar    finds the 1st bar ("bar" which has "foo" before it)
(?<!foo)bar    finds the 2nd bar ("bar" which does not have "foo" before it)

25. Not starts with ^(?!hede)\w*$
26. Not starts with and legnth is greater than ^(?!hede)\w{5,}$
hoho
hihi
haha
hede
asfhede

If you want to find a word not ending with an “s”, you could use «\b\w+(?<!s)\b».
27. \b\w+(?<!s)\b vs \b\w+[^s]\b vs \b\w+[^s\W]\b vs \b\w+[^s'\s]\b
ssbs
sdfsdf
sfs
sfsdgdg
John's
sdfas sdfa
sfsa
sds

Therefore, many regex flavors, including those used by Perl and Python, only allow fixed-length strings. You
can use any regex of which the length of the match can be predetermined

28. Let’s say we want to find a word that is six letters long and contains the three subsequent letters “cat”.
((\b\w{2}cat\w{1}\b)|(\b\w{3}cat\b)...)
cat\w{3}|\wcat\w{2}|\w{2}cat\w|\w{3}cat

RIGHT - (?=\b\w{6}\b)\w*cat\w*

caty
cat
sdfd cat
ascatu
dog
sdf cat s castcatdf s
sdfcat

29. So, what would you use to find any word between 6 and 12 letters long containing either “cat”, “dog” or
“mouse”? A
(?=\b\w{6,12}\b)\w*(cat|dog|mouse)\w*
cat
sdfd cat
ascatu
dog
sdf cat s castcatdf s
sdfcat
fk mouser we


Continuing at The End of The Previous Match \G
Applying «\G\w» to the string “test string” matches „t”. Applying it again matches „e”. The 3rd attempt yields „s” and the 4th attempt matches the second „t” in the string

 If-Then-Else Conditionals in Regular Expressions
 (?ifthen|else)
Using positive lookahead, the syntax becomes «(?(?=regex)then|else)»
30. (a)?b(?(1)c|d)
bd
abc
bc
abd

31. Extract Email Headers 
^((From|To)|Subject): ((?(2)\w+@\w+\.[a-z]+|.+))

If you precompile all the regular expressions, using multiple regular expressions will be
just as fast, if not faster, and the one big regex stuffed with conditionals

Adding Comments to Regular Expressions
(?#comment)
Valid email address matching
*/

/*
	valid date 
	«(19 | 20)\d\d[-/ .](0[1 - 9] | 1[012])[-/ .](0[1 - 9] | [12][0 - 9] | 3[01])»

	valid float
	[-+]?[0-9]*\.?[0-9]*
	[-+]?([0-9]*\.[0-9]+|[0-9]+)
	[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?
*/

void reg_match(const regex& re, const string& s)
{
	smatch match;
	if (regex_match(s, match, re))
	{
		cout << s << " found : " << match[0] << endl;
	}
}

void f1()
{
	regex re("gr[ae]y");
	string s1 = "gray";
	string s2 = "grey";
	string s3 = "graay";
	string s4 = "greey";
	vector<string> vs = { s1, s2, s3, s4 };

	for (const string& s : vs)
	{
		reg_match(re, s);
	}
}

void f2()
{
	regex pat("(AAAA)(BBB)?");
	string s = "AAAABBBBBB";
	smatch m;
	regex_search(s, m, pat);
	cout << boolalpha;
	cout << m[0].matched << '\n'; // true: we found a match
	cout << m[1].matched << '\n'; // true: there was a first sub_match
	cout << m[2].matched << '\n'; // false: no second sub_match
	cout << m[3].matched << '\n'; // false: there couldn’t be a third sub_match for pat

	cout << m[0] << endl;
	cout << m[1] << endl;
	cout << m[2] << endl;
}

void test_csv_parse()
{
	parse_csv ps;
	vector<migration_entry> v = ps.parse();

	for (const migration_entry& m : v)
	{
		cout << "migration info: \n";
		cout << m.year_month << ' ' << m.month_of_release << ' ' << m.passenger_type << ' ' << m.direction << ' ' << m.sex << ' ' << m.age << ' ' << m.estimate << ' ' << m.standard_error << ' ' << m.status << endl;

		cout << endl;
	}
}

int main()
{
	test_split();
	return 0;
}