
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

## TODO: should I ignore files mentioned in .Rbuildignore?
get_file_mapping <- function(project) {
    path <- file.path(project, "sugaR")
    src <- character(0)
    dest <- character(0)

    if (file.exists(path)) {
        filenames <- list.files(path, pattern = ".*[.][rR]")

        src <- file.path(project, "sugaR", filenames)
        dest <- file.path(project, "R", filenames)

        dir.create(file.path(project, "R"), showWarning = FALSE)
    }

    list(src = src, dest = dest)
}

desugar_file <- function(src, dest) {
    src <- path.expand(src)
    dest <- path.expand(dest)

    ast <- parse_file(src)
    desugar(ast)
    code <- unparse_str(ast)
    cat(code, file = dest, append = FALSE)
}

desugarProjectAddin <- function() {
    rstudioapi::verifyAvailable()

    project <- get_active_proj()

    if (is.null(project)) {
        rstudioapi::showDialog("Error", "No active project found")
        return(NULL)
    }

    mapping <- get_file_mapping(project)
    src <- mapping$src
    dest <- mapping$dest

    tryCatch(
        for (i in seq(1, length(src))) {
            desugar_file(src[i], dest[i])
        },
        error = function(e) {
            rstudioapi::showDialog("Error", e$message)
        }
    )
}

desugarFileAddin <- function() {
    rstudioapi::verifyAvailable()

    src <- get_active_file()
    project <- get_active_proj()

    if (is.null(src)) {
        rstudioapi::showDialog("Error", "No active file found")
        return(NULL)
    }

    filename <- basename(src)
    sugar_src <- file.path(project, "sugaR", filename)

    ## file is part of currently active project and inside the sugaR directory
    dest <- if (!is.null(project) && startsWith(src, project) && (src == sugar_src))
                file.path(project, "R", filename)
            else src

    desugar_file(src, dest)
}

resugarProjectAddin <- function() {
    rstudioapi::verifyAvailable()

}

resugarFileAddin <- function() {
    rstudioapi::verifyAvailable()
}
