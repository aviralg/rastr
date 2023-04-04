#' Sugar and Desugar AST
#'
#' @description
#' * `sugar()` sugars AST in-place by inserting strictness annotations
#' * `desugar()` Desugars AST in-place to well-formed R syntax
#'
#' @param ast AST object
#' @param node starting node for desugaring; defaults to AST root
#' @param table environment with function name as key and vector of strict
#' parameter positions as value
#' @name sugr

#' @rdname sugr
#' @export
desugar <- function(ast, node = ast_root_get(ast), strictness = TRUE) {
    .Call(C_rastr_desugar, ast, node, strictness)
}


#' @rdname sugr
#' @export
sugar <- function(ast, node = ast_root_get(ast), table) {
    .Call(C_rastr_sugar, ast, node, table)
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

#' @rdname sugr
#' @export
desugar_file <- function(sugr_file) {
    sugr_file <- path.expand(sugr_file)

    print(sugr_file)

    r_file <- gsub(".sugr$", ".R", sugr_file)

    ast <- parse_file(sugr_file)

    desugar(ast)
    code <- unparse_str(ast)

    cat(code, file = r_file, append = FALSE)
}

#' @rdname sugr
#' @export
desugar_project <- function(project_dir) {
    ## get all files in project with .sugr extension
    sugr_files <- list.files(project_dir,
                             recursive = TRUE,
                             pattern = ".*[.]sugr$",
                             full.names = TRUE)

    for (sugr_file in sugr_files) {
        desugar_file(sugr_file)
    }
}

desugarProjectAddin <- function() {
    rstudioapi::verifyAvailable()

    project_dir <- get_active_proj()

    if (is.null(project)) {
        rstudioapi::showDialog("Error", "No active project found")
        return(NULL)
    }

    project_dir <- path.expand(project_dir)

    tryCatch(
        desugar_project(project_dir),
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

#' @rdname sugr
#' @export
sugar_file <- function(r_file, table) {
    r_file <- path.expand(r_file)

    sugr_file <- if (endsWith(r_file, ".r")) gsub("\\.r$", ".sugr", r_file)
                 else gsub("\\.R$", ".sugr", r_file)

    ast <- parse_file(r_file)

    sugar(ast, table = table)

    code <- unparse_str(ast)

    cat(code, file = sugr_file, append = FALSE)
}

#' @rdname sugr
#' @export
sugar_project <- function(project_dir, table) {
    project_dir <- path.expand(project_dir)
    ## get all files in project with .R extension
    r_files <- list.files(file.path(project_dir, "R"),
                          recursive = FALSE,
                          pattern = ".*[.]R$",
                          ignore.case = TRUE,
                          full.names = TRUE)

    for (r_file in r_files) {
        sugar_file(r_file, table)
    }
}
