# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Leo Engine'
copyright = '2024-%Y, Lucas James'
author = 'Lucas James'
release = '0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = []

templates_path = ['_templates']
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
html_static_path = ['_static']
html_sidebars = {
    "**": [
        "about.html",
        "searchbox.html",
        "localtoc.html",
    ]
}

html_theme_options = {
    "description": "Engine for two-dimensional games written in C++. Developed by Turbo City Games.",
    "github_user": "amongfiish",
    "github_repo": "LeoEngine",
    "fixed_sidebar": True,
    "github_banner": False,
}

