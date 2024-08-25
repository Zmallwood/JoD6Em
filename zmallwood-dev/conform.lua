return {
  "stevearc/conform.nvim",
  opts = {
    formatters_by_ft = {
      cpp = { "uncrustify" },
    },
  },
  formatters = {
    injected = {
      command = "uncrustify",
      args = {"-c", "/root/uncrustify.cfg" ,"-f", "$FILENAME", "-o", "$FILENAME", "--no-backup"}
    }
  }
}
