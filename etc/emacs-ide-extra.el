;; Extra emacs file

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(eide-custom-c-indent-offset 3))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(message (concat eide-proj-dir "RsnSysErr"))

(defun my-semantic-hook-syserr ()
  (semantic-add-system-include (concat eide-proj-dir "RsnSysErr") 'c++-mode))
(add-hook 'semantic-init-hooks 'my-semantic-hook-syserr)
