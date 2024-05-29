local M = {}

local function find_header_files(dir)
  local results = {}
  local command = 'find "' .. dir .. '" -type f -name "*.h"'
  local p = io.popen(command)
  for file in p:lines() do
    table.insert(results, file)
  end
  return results
end

local function yank_file_content(file)
  local content = {}
  local start_yanking = false
  for line in io.lines(file) do
    if start_yanking then
      table.insert(content, line)
    elseif line:match("#pragma once") then
      start_yanking = true
    end
  end
  vim.fn.setreg('"', table.concat(content, "\n"))
end

function M.yank_snippet(snippet_name)
  local base_path = vim.fn.stdpath('data') .. '/lazy/catlicku/content'
  local content_path = vim.fn.resolve(base_path)
  local header_files = find_header_files(content_path)

  for _, file in ipairs(header_files) do
    local file_name = file:match("^.+/(.+)$")
    if file_name == snippet_name .. ".h" then
      yank_file_content(file)
      print("Yanked content from " .. file)
      return
    end
  end
  print("Snippet not found: " .. snippet_name)
end

vim.api.nvim_create_user_command('Uci', function(opts)
  M.yank_snippet(opts.args)
end, { nargs = 1 })

return M

