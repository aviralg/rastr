#' Desugar AST
#'
#' @description
#' * `desugar()` Desugars AST in-place to well-formed R syntax
#'
#' @param ast AST object
#' @param node starting node for desugaring; defaults to AST root
#' @name sugr

#' @rdname sugr
#' @export
desugar <- function(ast, node = ast_root_get(ast), strictness = TRUE) {
    .Call(C_rastr_desugar, ast, node, strictness)
}


################################################################################
## RStudio addins
################################################################################
get_active_file <- function() {
    ctxt <- rstudioapi::getSourceEditorContext()
    if (is.null(ctxt)) NULL
    else path.expand(ctxt$path)
}

get_active_proj <- function() {
    proj <- rstudioapi::getActiveProject()
    if (is.null(proj)) NULL
    else path.expand(proj)
}

desugar_file <- function(sugr_file) {
    sugr_file <- path.expand(sugr_file)

    r_file <- gsub(".sugr$", ".R", sugr_file)

    ast <- parse_file(sugr_file)

    desugar(ast)
    code <- unparse_str(ast)

    cat(code, file = r_file, append = FALSE)
}

desugarProjectAddin <- function() {
    rstudioapi::verifyAvailable()

    project <- get_active_proj()

    if (is.null(project)) {
        rstudioapi::showDialog("Error", "No active project found")
        return(NULL)
    }

    ## get all files in project with .sugr extension
    sugr_files <- list.files(project, recursive = TRUE, pattern = ".*[.]sugr$")

    tryCatch(
        for (sugr_file in sugr_files) {
            desugar_file(sugr_file)
        },
        error = function(e) {
            rstudioapi::showDialog("Error", e$message)
        }
    )
}

desugarFileAddin <- function() {
    rstudioapi::verifyAvailable()

    sugr_file <- get_active_file()

    ## if no active file, stop.
    if (is.null(sugr_file)) {
        rstudioapi::showDialog("Error", "No active file found")
        return(NULL)
    }

    ## if not a .sugr file, stop.
    if (!endsWith(sugr_file, ".sugr")) {
        rstudioapi::showDialog("Error", "File should end with '.sugr' extension")
        return(NULL)
    }

    desugar_file(sugr_file)
}
