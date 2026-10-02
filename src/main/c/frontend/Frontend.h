#ifndef FRONTEND_HEADER
#define FRONTEND_HEADER

#include "../support/logging/Logger.h"
#include "../support/type/CompilationStatus.h"
#include "../support/type/FlexContext.h"
#include "../support/type/Handler.h"
#include "../support/type/InputBuffer.h"
#include "../support/type/LexicalAnalyzer.h"
#include "../support/type/ModuleDestructor.h"
#include "../support/type/Token.h"
#include "../support/type/TokenLabel.h"
#include "lexical-analysis/FlexScanner.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
ModuleDestructor initializeFrontendModule(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Creates a new input buffer for the scanner.
 *
 * @see https://westes.github.io/flex/manual/Multiple-Input-Buffers.html
 */
InputBuffer * createInputBuffer(LexicalAnalyzer * lexicalAnalyzer, const char * path);

/**
 * Creates a new reentrant lexical-analyzer.
 *
 * @see https://westes.github.io/flex/manual/Reentrant.html
 */
LexicalAnalyzer * createLexicalAnalyzer();

/**
 * Creates a new token. You need to set the semantic-value after creation.
 */
Token * createToken(LexicalAnalyzer * lexicalAnalyzer, TokenLabel label);

/**
 * Returns the current lexical-analyzer context identifier.
 */
FlexContext currentLexicalAnalyzerContext(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Returns the current lexical-analysis handler.
 */
Handler currentLexicalAnalysisHandler();

/**
 * Returns the current syntactic-analysis handler.
 */
Handler currentSyntacticAnalysisHandler();

/**
 * Destroys an input buffer.
 */
void destroyInputBuffer(InputBuffer * inputBuffer);

/**
 * Destroys a lexical-analyzer and its resources.
 */
void destroyLexicalAnalyzer(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Destroys a token.
 */
void destroyToken(Token * token);

/**
 * Enters to a new nested lexical-analyzer context.
 */
void enterLexicalAnalyzerContext(LexicalAnalyzer * lexicalAnalyzer, FlexContext flexContext);

/**
 * Starts scanning the input until it reaches the end or fails.
 */
CompilationStatus executeLexicalAnalysis(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Starts parsing the input until it reaches the end or fails.
 */
CompilationStatus executeSyntacticAnalysis();

/**
 * Leaves the current nested lexical-analyzer context.
 */
void leaveLexicalAnalyzerContext(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Sets a handler that runs before every lexical-analysis actions.
 */
void onLexicalAnalysisAction(Handler handler);

/**
 * Sets a handler that runs before every syntactic-analysis actions.
 */
void onSyntacticAnalysisAction(Handler handler);

/**
 * Pops the current input buffer from the lexical-analyzer. Returns true if
 * there is more input buffers available; false otherwise.
 */
bool popInputBuffer(LexicalAnalyzer * lexicalAnalyzer);

/**
 * Pushes a new input buffer to merge its tokens into the stream.
 */
void pushInputBuffer(InputBuffer * inputBuffer);

/**
 * Pushes a new token to the parser input stream.
 */
CompilationStatus pushToken(LexicalAnalyzer * lexicalAnalyzer, Token * token);

#endif
