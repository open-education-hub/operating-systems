"use strict";

function strip_words(line) {
  const URL_REGEX = new RegExp(/https?:\/\/(www\.)?[-a-zA-Z0-9@:%._+~#=]{1,256}\.[a-zA-Z0-9()]{1,6}\b([-a-zA-Z0-9()@:%_+.~#?&//=]*)?/gi);
  const QUOTED_WORD_REGEX = new RegExp(/\`(.*?)\`|\"(.*?)\"/g)
  const IGNORED_REGEXES = [
    URL_REGEX,
    QUOTED_WORD_REGEX,
    'i.e.',
    'e.g.',
    'etc.',
    '...'
  ]

  IGNORED_REGEXES.forEach((i_word) => line = line.replace(i_word, ''))

  return line
}

module.exports = {
  names: ["MD104", "one line per sentence"],
  description: "one line (and only one line) per sentence",
  tags: ["sentences"],
  function: function rule(params, onError) {
    for (const inline of params.tokens.filter(function filterToken(token) {
      return token.type === "inline";
    })) {
      var actual_lines = inline.content.split("\n");
      actual_lines.forEach((line, index, arr) => {
        line = strip_words(line)
        let outside = true;
		let count = 0;
		Array.from(line).forEach((char) => {
			if ((char == "." || char == "?" || char == "!" || char == ";") && outside) {
				count++;
			}
			if (char == "`") outside = !outside;
			if (char == "[") outside = false;
			if (char == "(") outside = false;
			if (char == "]") outside = true;
			if (char == ")") outside = true;
		});
        if (count > 1) {
          onError({
            lineNumber: inline.lineNumber + index,
            detail:
              "Expected one sentence per line. Multiple end of sentence punctuation signs found on one line!",
          });
        }
      });
    }
  },
};
