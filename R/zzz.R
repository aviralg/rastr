.onLoad <- function(libname, pkgname) { # nolint
    .Call(C_rastr_initialize, parent.env(environment()))
}

.onUnload <- function(libpath) { # nolint
    .Call(C_rastr_finalize, parent.env(environment()))
}
