vim.api.nvim_create_autocmd(
--    { "BufEnter", "FocusGained", "InsertLeave", "WinEnter", "CmdlineLeave" },
    { "BufEnter" },
    {
        group = numbertoggle,
        callback = function()
            vim.opt.number = true

            local tn = vim.api.nvim_get_current_tabpage()
            local tree_win_handle = nil
            for _, window_handle in ipairs(vim.api.nvim_tabpage_list_wins(tn)) do
                local buffer_handle = vim.api.nvim_win_get_buf(window_handle)
                local buf_name = vim.fn.bufname(buffer_handle)
                if buf_name == "neo-tree filesystem [1]" then
                tree_win_handle = window_handle
                break
                end
            end
            if tree_win_handle == nil then
                -- Did not find window for neo-tree, could not reset size.
                return
            end
            vim.api.nvim_win_set_width(tree_win_handle, 55)
        end,
    }
)
