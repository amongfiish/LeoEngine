# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Turbo City'
copyright = '2025, Lucas James'
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
        "localtoc.html",
        "searchbox.html",
    ]
}

html_theme_options = {
    "description": "Test",
    "github_user": "amongfiish",
    "github_repo": "LeoEngine",
    "fixed_sidebar": True,
    "github_banner": True,
}

